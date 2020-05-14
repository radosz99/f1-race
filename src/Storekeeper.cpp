#include "Storekeeper.hpp"
#include "PitstopManager.hpp"
#include <iostream>

Storekeeper::Storekeeper(PitstopManager &pitstopManager): pitstopManager(pitstopManager),thread(&Storekeeper::run, this)
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
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout<<"Yo";
    }
}

void Storekeeper::setRaceCont(bool newRaceCont)
{
    raceCont = newRaceCont;
}