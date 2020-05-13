#pragma once
#include <thread>
#include "Pitstop.hpp"

class Engineer
{
public:
    Engineer(int id, Pitstop &pitstop);
    ~Engineer();
    void setRaceCont(bool value);
    void doActivity(int id);
    int activity = -1;
    int getSkill() const;
    
private:
    void run();
    bool raceCont;
    const int id;
    Pitstop &pitstop;
    float skill;
    std::thread thread;
};