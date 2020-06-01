#pragma once
#include "PitstopManager.hpp"
#include "StorekeeperState.hpp"
#include <array>
#include <mutex>
#include <thread>

class Storekeeper
{
public: 
    Storekeeper(std::array<Pitstop, 3>&pitstopes);
    ~Storekeeper();
    void setRaceCont(bool newRaceCont);
    std::string getStorekeeperStateString() const;
    int something = 0;
    int getSkill() const;
    float getProgress() const;

private:
    std::mutex mtx;
    std::atomic<StorekeeperState> state;
    std::thread thread;
    bool getWheel();
    std::array<Pitstop, 3>& pitstopes;
    void run();
    std::atomic<float> skill;
    std::atomic<float> progress;
    std::atomic<bool> raceCont = true;
};