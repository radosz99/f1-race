#pragma once
#include <string.h>
#include <random>
#include <atomic>
#include <thread>
#include <mutex>
#include "Road.hpp"
#include "State.hpp"
#include "Direction.hpp"
#include "Pitstop.hpp"
#include "PitstopManager.hpp"

class Bolide
{
public:
    Bolide(int id, Road &road,  PitstopManager &pitstopManager);
    ~Bolide();
    void run();
    std::string getStateString() const;
    std::string getDirectionString() const;
    Direction getDirection() const;
    int getId() const;
    int getFuelCondition() const;
    void setFuelCondition(float cond);
    void setState(State state);
    void fillFuelTank();
    PitstopManager &pitstopManager;
    Road &road;
    const float FUEL_RATIO_ALERT = 0.05f;
    int getFailureCounter() const;
    long getDistance() const;
    int getSkill() const;
    bool getOvertakingUp() const;
    int getTurbo() const;
    int getOvertakingCounter() const;
    int getPitstopId() const;


private:
    int waitingCounter = 0;
    int pitstopId = -1;
    int id;
    int failureCounter = 0;
    float skill;
    int turbo = 0;
    int overtakingCounter = 0;
    bool overtakingDown = false;
    bool overtakingUp = false;
    std::atomic<float> speed = 0.0f;
    std::thread thread;
    std::mutex mtx;
    std::atomic<long> distance = 0;
    std::atomic<float> fuelCondition;
    std::atomic<State> state = State::DRIVING;
    std::atomic<Direction> direction = Direction::RIGHT;
    std::pair<int,int> downMode(int x, int y);
    std::pair<int,int> leftDownMode(int x, int y, int &counter);
    std::pair<int,int> leftUpMode(int x, int y);
    std::pair<int,int> rightUpMode(int x, int y);
    std::pair<int,int> upMode(int x, int y);
    std::pair<int,int> upPSMode(int x, int y);
    std::pair<int,int> rightPSMode(int x, int y);
    std::pair<int,int> leftPSMode(int x, int y);
    std::pair<int,int> rightMode(int x, int y, int &counter);
    std::pair<int,int> leftMode(int x, int y);
};