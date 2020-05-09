#include "Bolide.hpp"
#include "Random.hpp"
#include "Direction.hpp"
#include "Pitstop.hpp"

Bolide::Bolide(int id, Road &road, const std::array<Pitstop, 3>& pitstopes): id(id), road(road), pitstopes(pitstopes), thread(&Bolide::run, this)
{
    fuelCondition = 1.0f;
    distance = 0;
}

Bolide::~Bolide()
{
    thread.join();
}

void Bolide::run()
{
    int counter = 0;
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
        std::scoped_lock lock(mtx);
        int x = road.getCoords(id).first;
        int y = road.getCoords(id).second;
        std::pair<int,int> newCoords;
        triesCounter++;

        //TODO: bug when cant change path (DOWN_UPTRACK -> DOWN_DOWNTRACK), should wait or go UP
        if(fuelCondition < FUEL_RATIO_ALERT && state == State::DRIVING && y < road.CHANGING_TRACK_BORDER)
        {
            state = State::DRIVING_NEED_TO_PIT_STOP;
        }

        if(state == State::DRIVING_NEED_TO_PIT_STOP && direction == Direction::RIGHT)
        {
            direction = Direction::RIGHT_DOWN;
        }

        if(direction == Direction::LEFT && y < 100 && x == road.UP_UPTRACK_COORD_X)
        {
            direction = Direction::LEFT_DOWN;
        }

        if(direction == Direction::RIGHT || direction == Direction::RIGHT_DOWN)
        {
           newCoords = rightMode(x, y, counter);
        }

        if(direction == Direction::UP)
        {
            newCoords = upMode(x, y);
        }

        if(direction == Direction::UP_PIT_STOP)
        {
            newCoords = upPSMode(x, y);
        }

        if(direction == Direction::LEFT)
        {
            newCoords = leftMode(x, y);
        }

        if(direction == Direction::LEFT_DOWN)
        {
            newCoords = leftDownMode(x, y, counter);
        }

        if(direction == Direction::DOWN)
        {
            newCoords = downMode(x, y);
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
    if(state == State::WAITING_FOR_PIT_STOP)
    {
        state = State::DRIVING;
        fillFuelTank();
    }
    int help_y = y - 1;
    if(!road.checkIfPositionOccupied(x, help_y, id))
    {
        y--;
    }
    else
    {
        failureCounter++;
    }
    
    if(y < road.BORDER_LEFT)
    {
        direction = Direction::DOWN;
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
    if(x < road.BORDER_UP)
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
    if(!road.checkIfPositionOccupied(help_x, y, id))
    {
        x--;
    }
    if(x < road.UP_UPTRACK_COORD_X)
    {
        //direction = Direction::LEFT_DOWN;
        direction = Direction::LEFT;
    }
    return std::make_pair(x, y);
}

std::pair<int,int> Bolide::leftDownMode(int x, int y, int &counter)
{
    int help_y = y - 1;
    int help_x = x;
    counter++;
    if(x < road.UP_DOWNTRACK_COORD_X) // if still changing path
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
std::pair<int,int> Bolide::rightMode(int x, int y, int &counter)
{
    int help_y = y + 1;
    int help_x = x;

    if(direction == Direction::RIGHT_DOWN)
    {
        counter++;
        if(x < road.DOWN_DOWNTRACK_COORD_X && counter > road.COORDS_DIFFERENCE) // if still changing path
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
            
    if(y > road.BORDER_RIGHT && state == State::DRIVING) // if right limit reached
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