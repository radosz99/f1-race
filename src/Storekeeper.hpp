#pragma once
#include "PitstopManager.hpp"
#include "StorekeeperState.hpp"
#include <array>
#include <thread>

class Storekeeper
{
public: 
    Storekeeper(std::array<Pitstop, 3>&pitstopes);
    ~Storekeeper();
    void setRaceCont(bool newRaceCont);
    std::string getStorekeeperStateString() const;
    int something = 0;
private:
    std::atomic<StorekeeperState> state = StorekeeperState::FREE;
    std::thread thread;
    bool getWheel();
    std::array<Pitstop, 3>& pitstopes;
    void run();
    std::atomic<bool> raceCont = true;
};