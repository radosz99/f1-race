#include "Bolide.hpp"
#include "Random.hpp"
#include "Direction.hpp"

Bolide::Bolide(int id, Road &road): id(id), road(road),thread(&Bolide::run, this)
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
        int delay = Random().randomInt(10 * (6-id), 80);
        mtx.lock();
        int x = road.getCoords(id).first;
        int y = road.getCoords(id).second;

        if(fuelCondition < 0.2 && state == State::DRIVING && y < 85)
        {
            setState(State::DRIVING_NEED_TO_PIT_STOP);
        }

        if(state == State::DRIVING_NEED_TO_PIT_STOP && direction == Direction::RIGHT)
        {
            direction = Direction::RIGHT_DOWN;
        }

        if(direction == Direction::DOWN or direction == Direction::UP)
        {
            delay *= 2;
        }


        if(direction == Direction::RIGHT || direction == Direction::RIGHT_DOWN)
        {
            int help_y = y + 1;
            int help_x = x;
            if(direction == Direction::RIGHT_DOWN)
            {
                counter++;
                if(x < 36 && counter > 3)
                {
                    help_x = help_x + 1;
                    counter = 0;
                }
                else
                {
                    direction = Direction::RIGHT;
                }
                
            }
            if(!road.checkIfPositionOccupied(x, help_y, Direction::RIGHT, id))
            {
                y = help_y;
                x = help_x;
            }
            
            if(y==109 && state == State::DRIVING)
            {
                direction = Direction::UP;
            }
            else if (state == State::DRIVING_NEED_TO_PIT_STOP && y == 130)
            {
                setState(State::WAITING_FOR_PIT_STOP);
                direction = Direction::UP;
            }
        }
        if(direction == Direction::UP)
        {
            int help_x = x - 1;
            if(!road.checkIfPositionOccupied(help_x, y, Direction::UP, id))
            {
                x--;
            }
            if(x==3)
            {
                direction = Direction::LEFT;
            }
        }
        if(direction == Direction::LEFT)
        {
            if(state == State::WAITING_FOR_PIT_STOP)
            {
                setState(State::DRIVING);
                fuelCondition = 1.0f;
            }
            int help_y = y - 1;
            if(!road.checkIfPositionOccupied(x, help_y, Direction::LEFT, id))
            {
                y--;
            }
            if(y==14)
            {
                direction = Direction::DOWN;
            }
        }
        if(direction == Direction::DOWN)
        {
            int help_x = x + 1;
            if(!road.checkIfPositionOccupied(help_x, y, Direction::DOWN, id))
            {
                x++;
            }
            if(x==29)
            {
                direction = Direction::RIGHT;
            }
        }
        road.setCoords(id, std::make_pair(x,y));
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
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
        case Direction::RIGHT:
            return "RIGHT";
        case Direction::UP:
            return "UP";
        case Direction::LEFT:
            return "LEFT";
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

