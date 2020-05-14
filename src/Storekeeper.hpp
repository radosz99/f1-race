#pragma once
#include "PitstopManager.hpp"
#include <array>
#include <thread>

class Storekeeper
{
public: 
    Storekeeper(PitstopManager &pitstopManager);
    ~Storekeeper();
    void setRaceCont(bool newRaceCont);
    
private:
    std::thread thread;
    PitstopManager &pitstopManager;
    void run();
    std::atomic<bool> raceCont = true;
};