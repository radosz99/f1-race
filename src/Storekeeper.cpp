#include "Storekeeper.hpp"
#include "PitstopManager.hpp"
#include <iostream>

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
        //TODO: probably Storekeeper threads still working after ESC
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(getWheel())
        {
            state = StorekeeperState::RECYCLING;
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            state = StorekeeperState::FREE;
            pitstopes[0].setWheelStock(pitstopes[0].getWheelStock() + 1);
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
        something = 2;
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