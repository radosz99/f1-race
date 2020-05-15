#include "Storekeeper.hpp"
#include "PitstopManager.hpp"
#include <iostream>
#include<bits/stdc++.h> 

Storekeeper::Storekeeper(std::array<Pitstop, 3>&pitstopes): pitstopes(pitstopes),thread(&Storekeeper::run, this)
{

}

Storekeeper::~Storekeeper()
{
    thread.join();
}

void Storekeeper::run()
{
    while(raceCont)
    {
        //std::cout<<raceCont;
        //TODO: filling fuel tank
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(getWheel())
        {
            state = StorekeeperState::RECYCLING;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
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
    }
}

void Storekeeper::setRaceCont(bool newRaceCont)
{
    raceCont = newRaceCont;
}

bool Storekeeper::getWheel()
{
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

std::string Storekeeper::getStorekeeperStateString()const
{
    switch(state)
    {
        case StorekeeperState::FREE:
            return "FREE";
        case StorekeeperState::RECYCLING:
            return "RECYCLING";
        case StorekeeperState::SEARCHING:
            return "SEARCHING";
    }
}