#include "Bolide.hpp"
#include "Random.hpp"
#include "Direction.hpp"
#include "Pitstop.hpp"
#include "PitstopState.hpp"

Bolide::Bolide(int id, Road &road, std::array<Pitstop, 3>& pitstopes): id(id), road(road), pitstopes(pitstopes), thread(&Bolide::run, this)
{
    fuelCondition = 0.2f;
    distance = 0;
}

Bolide::~Bolide()
{
    thread.join();
}

void Bolide::run()
{
    int counter = 0;
    int pitstopCounter = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    while(!road.getRaceCont());
    while(road.getRaceCont())
    {
        fuelCondition = fuelCondition * 0.995;
        int delay = Random().randomInt(15 * (6-id), 100);
        
        if(direction == Direction::DOWN || direction == Direction::UP || direction == Direction::UP_PIT_STOP)
        {
            delay *= road.COORDS_DIFFERENCE;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        //TODO: fix bug with too fast free state in pitstop
        //TODO: make pitstop manager
        //TODO: add overtaking mode in both up and down paths
        if(state == State::PIT_STOP)
        {
            pitstopCounter++;
            if(pitstopCounter < 50)
            {
                continue;
            }
            pitstopCounter = 0;
            state = State::AFTER_PIT_STOP;
            direction = Direction::LEFT_PIT_STOP;

        }
        std::scoped_lock lock(mtx);

        int x = road.getCoords(id).first;
        int y = road.getCoords(id).second;
        std::pair<int,int> newCoords;
        triesCounter++;

        if(state == State::WAITING_FOR_PIT_STOP) // looking for available pitstop
        {
            for(size_t i = 0; i < pitstopes.size(); i++)
            {
                if(pitstopes[i].getStatus() == PitstopState::FREE)
                {
                    pitstopId = i;
                    pitstopes[pitstopId].setStatus(PitstopState::WAITING_FOR_BOLIDE);
                    state = State::DRIVING_TO_PIT_STOP;
                    break;
                }
            }
        }

        //TODO: bug when cant change path (DOWN_UPPATH -> DOWN_DOWNPATH), should wait or go UP
        if(fuelCondition < FUEL_RATIO_ALERT && state == State::DRIVING && y < road.CHANGING_PATH_BORDER) // if pitstop is needed and position is right
        {
            state = State::DRIVING_NEED_TO_PIT_STOP;
        }

        if(state == State::DRIVING_NEED_TO_PIT_STOP && direction == Direction::RIGHT) // change path to downtrack to get to the pitstop
        {
            direction = Direction::RIGHT_DOWN;
        }

        if(direction == Direction::LEFT && y < 100 && x == road.UP_UPPATH_COORD_X) // change uptrack to downtrack if coords are right
        {
            direction = Direction::LEFT_DOWN;
        }

        switch(direction)
        {
            case Direction::RIGHT:
                newCoords = rightMode(x, y, counter);
                break;
            case Direction::RIGHT_DOWN:
                newCoords = rightMode(x, y, counter);
                break;
            case Direction::UP:
                newCoords = upMode(x, y);
                break;
            case Direction::UP_PIT_STOP:
                newCoords = upPSMode(x, y);
                break;
            case Direction::LEFT:
                newCoords = leftMode(x, y);
                break;
            case Direction::LEFT_DOWN:
                newCoords = leftDownMode(x, y, counter);
                break;
            case Direction::DOWN:
                newCoords = downMode(x, y);
                break;
            case Direction::RIGHT_PIT_STOP:
                newCoords = rightPSMode(x, y);
                break;
            case Direction::LEFT_PIT_STOP:
                newCoords = leftPSMode(x, y);
                break;
        }

        road.setCoords(id, newCoords);
    }
}

std::pair<int,int> Bolide::downMode(int x, int y)
{
    int help_x = x + 1;
    if(!road.checkIfPositionOccupied(help_x, y, id))
    {
        x++;
    }
    if(x > road.BORDER_DOWN)
    {
        direction = Direction::RIGHT;
    }
    return std::make_pair(x, y);
}

std::pair<int,int> Bolide::leftMode(int x, int y)
{
    int help_y = y - 1;

    if(!road.checkIfPositionOccupied(x, help_y, id))
    {
        y--;
    }
    else
    {
        failureCounter++;
    }
    
    if(y <= road.BORDER_LEFT)
    {
        direction = Direction::DOWN;
    }
    return std::make_pair(x, y);
}

std::pair<int,int> Bolide::leftPSMode(int x, int y)
{
    int help_y = y - 1;

    if(!road.checkIfPositionOccupied(x, help_y, id))
    {
        y--;
    }
    
    if(y <= road.PIT_STOP_BORDER_RIGHT)
    {
        fillFuelTank();
        pitstopes[pitstopId].setStatus(PitstopState::FREE);
        pitstopId = -1;
        direction = Direction::UP_PIT_STOP;
    }
    return std::make_pair(x, y);
}


std::pair<int,int> Bolide::upMode(int x, int y)
{
    int help_x = x - 1;
    if(!road.checkIfPositionOccupied(help_x, y, id))
    {
        x--;
    }
    if(x <= road.BORDER_UP)
    {
        direction = Direction::LEFT;
        failureCounter = 0;
        triesCounter = 0;
    }
    return std::make_pair(x, y);
}

std::pair<int,int> Bolide::upPSMode(int x, int y)
{
    int help_x = x - 1;
    if(pitstopId < 0 && state != State::AFTER_PIT_STOP)
    {
        return std::make_pair(x, y);
    }
    if(!road.checkIfPositionOccupied(help_x, y, id))
    {
        x--;
    }
    if(x <= road.UP_UPPATH_COORD_X)
    {
        state = State::DRIVING;
        direction = Direction::LEFT;
        return std::make_pair(x, y);
    }

    if(x <= road.PIT_STOP_COORD_X - 10 * pitstopId && state != State::AFTER_PIT_STOP)
    {
        direction = Direction::RIGHT_PIT_STOP;
    }
    return std::make_pair(x, y);
}

std::pair<int,int> Bolide::leftDownMode(int x, int y, int &counter)
{
    int help_y = y - 1;
    int help_x = x;
    counter++;
    if(x < road.UP_DOWNPATH_COORD_X) // if still changing path
    {
        help_x = help_x + 1;
        counter = 0;
    }
    else // if path-change is done
    {
        direction = Direction::LEFT;
        failureCounter = 0;
        triesCounter = 0;
    }

    if(!road.checkIfPositionOccupied(help_x, help_y, id))
    {
        y--;
        x = help_x;
    }
    if(y < road.BORDER_LEFT)
    {
        direction = Direction::DOWN;
    }
    return std::make_pair(x, y);
}

std::pair<int,int> Bolide::rightPSMode(int x, int y)
{
    int help_y = y + 1;

    if(!road.checkIfPositionOccupied(x, help_y, id))
    {
        y = help_y;
    }
            
    if(y > road.PIT_STOP_COORD_Y) // if right limit reached
    {
        //direction = Direction::LEFT;
        state = State::PIT_STOP;
        pitstopes[pitstopId].setStatus(PitstopState::BUSY);
        
    }
    return std::make_pair(x, y);
}


std::pair<int,int> Bolide::rightMode(int x, int y, int &counter)
{
    int help_y = y + 1;
    int help_x = x;

    if(direction == Direction::RIGHT_DOWN)
    {
        counter++;
        if(x < road.DOWN_DOWNPATH_COORD_X && counter > road.COORDS_DIFFERENCE) // if still changing path
        {
            help_x = help_x + 1;
            counter = 0;
        }
        else // if path-change is done
        {
            direction = Direction::RIGHT;
        }
    }
    if(!road.checkIfPositionOccupied(help_x, help_y, id))
    {
        y = help_y;
        x = help_x;
    }
            
    if(y >= road.BORDER_RIGHT && state == State::DRIVING) // if right limit reached
    {
        direction = Direction::UP;
    }

    else if (state == State::DRIVING_NEED_TO_PIT_STOP && y >= road.PIT_STOP_BORDER_RIGHT)
    {
        state = State::WAITING_FOR_PIT_STOP;
        direction = Direction::UP_PIT_STOP;
    }
    return std::make_pair(x, y);
}

Direction Bolide::getDirection() const
{
    return direction;
}

std::string Bolide::getDirectionString() const
{
    switch (direction)
    {
        case Direction::DOWN:
            return "DOWN";
        case Direction::RIGHT_DOWN:
            return "RIGHT_DOWN";
        case Direction::LEFT_DOWN:
            return "LEFT_DOWN";
        case Direction::RIGHT:
            return "RIGHT";
        case Direction::UP:
            return "UP";
        case Direction::LEFT:
            return "LEFT";
        case Direction::UP_PIT_STOP:
            return "UP_PIT_STOP";
        case Direction::RIGHT_PIT_STOP:
            return "RIGHT_PIT_STOP";
        case Direction::LEFT_PIT_STOP:
            return "LEFT_PIT_STOP";
    }   
}

void Bolide::setState(State stat)
{
    state = stat;
}

float Bolide::getFuelCondition() const
{
    return fuelCondition;
}

int Bolide::getId() const
{
    return id;
}

void Bolide::setFuelCondition(float cond)
{
    fuelCondition = cond;
}

std::string Bolide::getStateString() const
{
    switch (state)
    {
        case State::DRIVING:
            return "DRIVING";
        case State::DRIVING_NEED_TO_PIT_STOP:
            return "DRIVING_NEED_TO_PIT_STOP";
        case State::WAITING_FOR_PIT_STOP:
            return "WAITING_FOR_PIT_STOP";
        case State::PIT_STOP:
            return "PIT_STOP";
        case State::AFTER_PIT_STOP:
            return "AFTER_PIT_STOP";
        case State::DRIVING_TO_PIT_STOP:
            return "DRIVING_TO_PIT_STOP";
    }
}

void Bolide::fillFuelTank()
{
    fuelCondition = 1.0f;
}

int Bolide::getFailureCounter() const
{
    return failureCounter;
}
int Bolide::getTriesCounter() const
{
    return triesCounter;
}