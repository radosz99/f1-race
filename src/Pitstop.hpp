#pragma once
#include<atomic>
#include<mutex>
#include"PitstopState.hpp"

class Pitstop
{
public:
    Pitstop(int id);
    PitstopState getStatus() const;
    void setStatus(PitstopState newStatus);
    int getId() const;
    std::string getStateString() const;

private:
    PitstopState status = PitstopState::FREE;
    std::mutex mtx;
    const int id;

};