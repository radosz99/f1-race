#pragma once
#include <thread>

class Engineer
{
public:
    Engineer(int id, int pitstopId);
    ~Engineer();
    void setRaceCont(bool value);
    
private:
    void run();
    bool raceCont;
    const int id;
    const int pitstopId;
    float skill;
    std::thread thread;
};