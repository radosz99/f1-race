#include "Bolide.hpp"
#include "Random.hpp"
#include "Direction.hpp"
#include "Pitstop.hpp"
#include "PitstopState.hpp"
#include "PitstopManager.hpp"
#include <iostream>

Bolide::Bolide(int id, Road &road, PitstopManager &pitstopManager): id(id), road(road), pitstopManager(pitstopManager), thread(&Bolide::run, this)
{
    fuelCondition = static_cast<float> (static_cast<float>(Random().randomInt(40,100))/100);
    skill = static_cast<float> (static_cast<float>(Random().randomInt(20,90))/100);
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
        fuelCondition = fuelCondition * 0.997;
        int minimumDelay = (25 - 15*fuelCondition)/skill - turbo;
        int delay = Random().randomInt(minimumDelay, minimumDelay + 20);
        
        if(direction == Direction::DOWN || direction == Direction::UP || direction == Direction::UP_PIT_STOP)
        {
            delay *= road.COORDS_DIFFERENCE;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));

        if(state == State::PIT_STOP)
        {
            pitstopManager.makePitstop(pitstopId,fuelCondition);
            state = State::AFTER_PIT_STOP;
            direction = Direction::LEFT_PIT_STOP;

        }
        std::scoped_lock lock(mtx);

        int x = road.getCoords(id).first;
        int y = road.getCoords(id).second;
        std::pair<int,int> newCoords;

        if(state == State::WAITING_FOR_PIT_STOP) // looking for available pitstop
        {
            pitstopId = pitstopManager.getFreePitstop();
            if(pitstopId != -1)
            {
                state = State::DRIVING_TO_PIT_STOP;
            }
        }

        if(!road.checkIfPositionOccupied(x + 1 , y + 1, id) && overtakingUp)
        {
            failureCounter = 0;
            if(overtakingCounter < 75)
            {
                overtakingCounter++;
            }

            else
            {
                overtakingUp = false;
                turbo = 0;
            }
        }

        if(fuelCondition < FUEL_RATIO_ALERT && state == State::DRIVING && y < road.CHANGING_PATH_BORDER) // if pitstop is needed and position is right
        {
            state = State::DRIVING_NEED_TO_PIT_STOP;
        }

        if(state == State::DRIVING_NEED_TO_PIT_STOP && direction == Direction::RIGHT) // change path to downtrack to get to the pitstop
        {
            direction = Direction::DOWN_TO_PITSTOP;
        }

        if(direction == Direction::LEFT && y < 100 && x == road.UP_UPPATH_COORD_X && direction != Direction::LEFT_UP && !overtakingUp) // change uptrack to downtrack if coords are right
        {
            direction = Direction::LEFT_DOWN;
        }

        switch(direction)
        {
            case Direction::RIGHT:
                newCoords = rightMode(x, y, counter);
                break;
            case Direction::DOWN_TO_PITSTOP:
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
            case Direction::LEFT_UP:
                newCoords = leftUpMode(x, y);
                break;
            case Direction::RIGHT_UP:
                newCoords = rightUpMode(x, y);
                break;
        }
        // sekcja krytyczna
        road.setCoords(id, newCoords);
    }
}

std::pair<int,int> Bolide::downMode(int x, int y)
{
    failureCounter = 0;
    overtakingCounter = 0;
    overtakingUp = false;
    turbo = 0;
    int help_x = x + 1;
    if(!road.checkIfPositionOccupied(help_x, y, id))
    {
        x++;
    }
    if(x > road.BORDER_DOWN)
    {
        distance++;
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
        if(failureCounter > 3 && y > road.BORDER_LEFT + 15 && !road.checkIfPositionOccupied(x-4, y, id)){
            turbo = 20;
            overtakingUp = true;
            waitingCounter = 0;
            direction = Direction::LEFT_UP;
        }
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
        pitstopManager.getPitstopes()[pitstopId].notifyAll();
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
    overtakingCounter = 0;
    
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

std::pair<int,int> Bolide::leftUpMode(int x, int y)
{
    if(waitingCounter > 20)
    {
        direction = Direction::LEFT;
        failureCounter = 0;
        return std::make_pair(x, y);
    }

    int help_y = y - 1;
    int help_x = x;
    if(x > road.UP_UPPATH_COORD_X) // if still changing path
    {
        help_x = help_x - 1;
    }
    else // if path-change is done
    {
        direction = Direction::LEFT;
        failureCounter = 0;
    }

    if(!road.checkIfPositionOccupied(help_x, help_y, id))
    {
        y--;
        x = help_x;
    }
    else
    {
        waitingCounter++;
    }
    if(y < road.BORDER_LEFT)
    {
        waitingCounter = 0;
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
        state = State::PIT_STOP;
    }
    return std::make_pair(x, y);
}


std::pair<int,int> Bolide::rightMode(int x, int y, int &counter)
{
    int help_y = y + 1;
    int help_x = x;

    if(direction == Direction::DOWN_TO_PITSTOP)
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

        if(y > road.BORDER_RIGHT) // if border is too closer
        {
            direction = Direction::RIGHT;
        }
    }

    if(!road.checkIfPositionOccupied(help_x, help_y, id))
    {
        y = help_y;
        x = help_x;
    }
            
    if(y >= road.BORDER_RIGHT && state == State::DRIVING || (state == State::DRIVING_NEED_TO_PIT_STOP && x < road.DOWN_DOWNPATH_COORD_X && y >= road.BORDER_RIGHT)) // if right limit reached
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

std::pair<int,int> Bolide::rightUpMode(int x, int y)
{
    int help_y = y + 1;
    int help_x = x;
    if(x > road.UP_UPPATH_COORD_X) // if still changing path
    {
        help_x = help_x - 1;
    }
    else // if path-change is done
    {
        direction = Direction::LEFT;
        failureCounter = 0;
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
        case Direction::DOWN_TO_PITSTOP:
            return "DOWN_TO_PITSTOP";
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
        case Direction::LEFT_UP:
            return "LEFT_UP";
    }   
}

void Bolide::setState(State stat)
{
    state = stat;
}

int Bolide::getFuelCondition() const
{
    return static_cast<int>(fuelCondition * 100);
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


int Bolide::getSkill() const
{
    return static_cast<int>(skill * 100);
}

bool Bolide::getOvertakingUp() const
{
    return overtakingUp;
}

int Bolide::getTurbo() const
{
    return turbo;
}

int Bolide::getOvertakingCounter() const
{
    return overtakingCounter;
}

int Bolide::getPitstopId() const
{
    return pitstopId;
}

long Bolide::getDistance() const
{
    return distance;
}
