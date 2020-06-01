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

bool Road::checkIfPositionOccupied(int x, int y, int index)
{
    std::scoped_lock lock(checkMutex);
    for(int i = 0; i < 14; i++)
    {
        if(index == i)
        {
            continue;
        }
        int first = coords[i].first;
        int second = coords[i].second;

        if(((first <= x && x <= first + BOLID_HEIGHT - 1) || (first <= x + BOLID_HEIGHT - 1 && x + BOLID_HEIGHT - 1 <= first + BOLID_HEIGHT - 1)) 
            && ((second <= y && y <= second + BOLID_WIDTH- 1) || (second <= y + BOLID_WIDTH- 1 && y + BOLID_WIDTH- 1 <= second + BOLID_WIDTH- 1)))
        {
            return true;
        }
    }
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