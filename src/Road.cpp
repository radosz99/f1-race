#include "Road.hpp"

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

bool Road::checkIfPositionOccupied(int x, int y, char direction, int index)
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

        if(direction=='u')
        {
            if(x - 4 < first && x > first && y < second + 7 && y >= second)
            {
                checkMutex.unlock();
                return true;
            }
        }
        if(direction=='d')
        {
            if(x + 4 > first && x < first && y < second + 7 && y >= second)
            {
                checkMutex.unlock();
                return true;
            }
        }
        if(direction=='r')
        {
            if(y + 7 > second && y < second && x < first + 4 && x >= first)
            {
                checkMutex.unlock();
                return true;
            }
            
        }
        if(direction=='l')
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