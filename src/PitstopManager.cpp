#include "PitstopManager.hpp"
#include "Random.hpp"
#include <thread>

std::array<Pitstop, 3> &PitstopManager::getPitstopes() 
{
	return pitstopes;
}

// std::array<Engineer, 9> &PitstopManager::getEngineers() 
// {
// 	return engineers;
// }

PitstopManager::PitstopManager()
{

}

PitstopManager::~PitstopManager()
{
    
}

int PitstopManager::getFreePitstop()
{
    std::scoped_lock(askingMutex);
    int pitstopId = -1;
    bool free = false;
    while(!free)
    {
        for(size_t i = 0; i < pitstopes.size(); i++)
        {
            if(pitstopes[i].getStatus() == PitstopState::FREE)
            {
                pitstopId = i;
                free = true;
                pitstopes[pitstopId].setStatus(PitstopState::WAITING_FOR_BOLIDE);
                break;
            }
        }
    }
    return pitstopId;
}

void PitstopManager:: makePitstop(int pitstopId)
{
    pitstopes[pitstopId].setStatus(PitstopState::BUSY);
    int delayCount = Random().randomInt(100, 160);

	for (int i = 1; i <= delayCount; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		pitstopes[pitstopId].setFuelProgress(static_cast<float>(i) / static_cast<float>(delayCount));
	}
	//progress = 0.0f;
}
