#include "Bolide.hpp"
#include "Random.hpp"

Bolide::Bolide(int x, int y, char dir, int id, Road &road): x(x), y(y), direction(dir), id(id), road(road),thread(&Bolide::run, this)
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
    while(true)
    {
        fuelCondition = fuelCondition * 0.99;
        int delay = Random().randomInt(60, 150);
        if(direction =='d' or direction == 'u')
        {
            delay*=2;
        }
        if(direction == 'r')
        {
            int help_y = y + 1;
            if(!road.checkIfPositionOccupied(x, help_y, 'r', id))
            {
                y++;
            }
            if(y==109)
            {
                direction = 'u';
            }
        }
        if(direction == 'u')
        {
            int help_x = x - 1;
            if(!road.checkIfPositionOccupied(help_x, y, 'u', id))
            {
                x--;
            }
            if(x==3)
            {
                direction = 'l';
            }
        }
        if(direction == 'l')
        {
            int help_y = y - 1;
            if(!road.checkIfPositionOccupied(x, help_y, 'l', id))
            {
                y--;
            }
            if(y==14)
            {
                direction = 'd';
            }
        }
        if(direction == 'd')
        {
            int help_x = x + 1;
            if(!road.checkIfPositionOccupied(help_x, y, 'd', id))
            {
                x++;
            }
            if(x==29)
            {
                direction = 'r';
            }
        }
        road.setCoords(id, std::make_pair(x,y));

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

int Bolide::getX() const
{
    return x;
}

int Bolide::getY() const
{
    return y;
}

void Bolide::setDirection(char dir)
{
    direction = dir;
}

char Bolide::getDirection() const
{
    return direction;
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

