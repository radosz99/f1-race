#include "TrackManager.hpp"
#include "TrackSetup.hpp"
TrackManager::TrackManager()
{
    TrackSetup setup(this);
}

TrackManager::~TrackManager()
{
}

bool TrackManager::checkIfPositionOccupied(int x, int y, char direction)
{
    checkMutex.lock();
    for(size_t i; i < bolides.size(); i++)
    {
        if(direction=='u')
        {
            if(bolides[i].getX()+4 < x)
            {
                return true;
            }
        }
        if(direction=='d')
        {
            if(bolides[i].getX()+4 < x)
            {
                return true;
            }
        }
        if(direction=='r')
        {
            if(bolides[i].getY()-4 < y)
            {
                return true;
            }
        if(direction=='l')
        {           
            if(bolides[i].getY()+4 < y)
            {
                return true;
            }

        }
    }
    checkMutex.unlock();
    return false;
}

const std::array<Bolide, 6> & TrackManager::getBolides() {
	return bolides;
}