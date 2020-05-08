#include "Bolide.hpp"
#include "Random.hpp"

Bolide::Bolide(int x, int y, char dir, std::string name): x(x), y(y), direction(dir), name(name), thread(&Bolide::run, this)
{
    fuelCondition = 1.0f;
}

Bolide::~Bolide()
{
    thread.join();
}

void Bolide::run()
{
    while(true)
    {
        fuelCondition*=0.99;
        int delay = Random().randomInt(15, 100);
        if(direction == 'r')
        {
            
            y++;
            if(y==105)
            {
                direction = 'u';
            }
        }
        if(direction == 'u')
        {
            x--;
            if(x==4)
            {
                direction = 'l';
            }
        }
        if(direction == 'l')
        {
            y--;
            if(y==14)
            {
                direction = 'd';
            }
        }
        if(direction == 'd')
        {
            x++;
            if(x==34)
            {
                direction = 'r';
            }
        }

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

std::string Bolide::getName() const
{
    return name;
}

void Bolide::setFuelCondition(float cond)
{
    fuelCondition = cond;
}