#include "PitstopManager.hpp"
#include "Random.hpp"
#include <thread>

std::array<Pitstop, 3> &PitstopManager::getPitstopes() 
{
	return pitstopes;
}

std::array<Engineer, 9> &PitstopManager::getEngineers() 
{
	return engineers;
}

PitstopManager::PitstopManager()
{

}

PitstopManager::~PitstopManager()
{
    
}

int PitstopManager::getFreePitstop()
{
    //TODO: bug when sometimes two bolides get the same pitstop (they are really close to each other)
    std::scoped_lock(askingMutex);
    int pitstopId = -1;
    bool free = false;
    while(!free && raceCont)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));  
        for(size_t i = 0; i < pitstopes.size(); i++)
        {
            if(pitstopes[i].getStatus() == PitstopState::FREE)
            {
                pitstopId = i;
                free = true;
                pitstopes[i].setStatus(PitstopState::WAITING_FOR_BOLIDE);
                return pitstopId;
            }
        }
    }
}

void PitstopManager:: makePitstop(int pitstopId, float fuelCondition)
{
    pitstopes[pitstopId].setStatus(PitstopState::BUSY);
    pitstopes[pitstopId].fuelNeeded = 1 - fuelCondition;

    while(!pitstopes[pitstopId].fuelReady || !pitstopes[pitstopId].firstWheelReady|| !pitstopes[pitstopId].secondWheelReady ||
            !pitstopes[pitstopId].thirdWheelReady || !pitstopes[pitstopId].fourthWheelReady && raceCont)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));    
    }
}

void PitstopManager::setRaceCont(bool newRaceCont)
{
    raceCont = newRaceCont;
    for(size_t i = 0; i < pitstopes.size(); i++)
    {
        pitstopes[i].notifyAll();
    }
}