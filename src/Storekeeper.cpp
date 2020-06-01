#include "Storekeeper.hpp"
#include "PitstopManager.hpp"
#include "Random.hpp"
#include <iostream>
#include<bits/stdc++.h> 

Storekeeper::Storekeeper(std::array<Pitstop, 3>&pitstopes): pitstopes(pitstopes),thread(&Storekeeper::run, this)
{
    skill = static_cast<float> (static_cast<float>(Random().randomInt(20,100))/100);
}

Storekeeper::~Storekeeper()
{
    std::cout << "Storekeeper end" << std::endl;
    thread.join();
}

void Storekeeper::run()
{
    while(raceCont)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(getWheel())
        {
            state = StorekeeperState::WHEEL_RECYCLING;
            int delayCount = 150 - 80 * skill;
            for (int i = 1; i <= delayCount && raceCont; i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                progress = static_cast<float>(i) / static_cast<float>(delayCount);
            }

            std::scoped_lock(pitstopes[0].wheelStockMtx, pitstopes[1].wheelStockMtx, pitstopes[2].wheelStockMtx);
            int min = INT_MAX;
            int pitstopId = 0;
            for(size_t i = 0; i < pitstopes.size(); i++)
            {
                if(pitstopes[i].getWheelStock() < min)
                {
                    min = pitstopes[i].getWheelStock();
                    pitstopId = i;
                }
            }
            pitstopes[pitstopId].setWheelStock(pitstopes[pitstopId].getWheelStock() + 1);
            pitstopes[pitstopId].notify();
        }

        for(size_t i = 0; i < pitstopes.size(); i++)
        {
            if(pitstopes[i].getFuelStock() < 5)
            {
                state = StorekeeperState::REFUELING;
                int delayCount = 180 - 80 * skill;
                for (int j = 1; j <= delayCount && raceCont; j++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    progress = static_cast<float>(j) / static_cast<float>(delayCount);
                    pitstopes[i].setFuelStock(pitstopes[i].getFuelStock() + 0.05);
                }
                break;
            }
        }
    }
}

void Storekeeper::setRaceCont(bool newRaceCont)
{
    raceCont = newRaceCont;
}

bool Storekeeper::getWheel()
{
    std::scoped_lock(mtx);
    state = StorekeeperState::SEARCHING;
    for (size_t i; i < pitstopes.size(); i++)
    {
        if(pitstopes[i].getUsedWheels() > 0)
        {
            pitstopes[i].setUsedWheels(pitstopes[i].getUsedWheels() - 1);
            return true;    
        }
    }
    return false;
}

float Storekeeper::getProgress() const
{
    return progress;
}

std::string Storekeeper::getStorekeeperStateString()const
{
    switch(state)
    {
        case StorekeeperState::REFUELING:
            return "REFUELING";
        case StorekeeperState::WHEEL_RECYCLING:
            return "WHEEL_RECYCLING";
        case StorekeeperState::SEARCHING:
            return "SEARCHING";
        default:
            return "FREE";
    }
}
