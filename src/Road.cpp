#include "Road.hpp"
#include "Direction.hpp"
Road::Road()
{

}
std::pair<int, int> Road::getCoords(int index)
{
    return coords[index];
}

std::pair<int, int> *Road::getAllCoords()
{
    return coords;
}
 
 
void Road::setCoords(int index, std::pair<int, int>  coord)
{
    coords[index] = coord;
}

bool Road::checkIfPositionOccupied(int x, int y, Direction direction, int index)
{
    checkMutex.lock();
    for(int i = 0; i < 6; i++)
    {
        if(index == i)
        {
            continue;
        }
        int first = coords[i].first;
        int second = coords[i].second;

        if(direction == Direction::UP)
        {
            if(x - 4 < first && x > first && y < second + 7 && y >= second)
            {
                checkMutex.unlock();
                return true;
            }
        }
        if(direction == Direction::DOWN)
        {
            if(x + 4 > first && x < first && y < second + 7 && y >= second)
            {
                checkMutex.unlock();
                return true;
            }
        }
        if(direction == Direction::RIGHT)
        {
            if(y + 7 > second && y < second && x < first + 4 && x >= first)
            {
                checkMutex.unlock();
                return true;
            }
            
        }
        if(direction == Direction::LEFT)
        {           
            if(y - 7 < second && y > second && x < first + 4 && x >= first)
            {
                checkMutex.unlock();
                return true;
            }

        }
    }
    checkMutex.unlock();
    return false;
}

void Road::setRaceCont(bool cont)
{
    race_cont = cont;
}

bool Road::getRaceCont() const
{
    return race_cont;
}