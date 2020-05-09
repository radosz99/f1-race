#pragma once
#include <string.h>
#include <random>
#include <atomic>
#include <thread>
#include <mutex>
#include"Road.hpp"
#include"State.hpp"
#include"Direction.hpp"

class Bolide
{
public:
    Bolide(int id, Road &road);
    ~Bolide();
    void run();
    std::string getStateString() const;
    std::string getDirectionString() const;
    Direction getDirection() const;
    int getId() const;
    float getFuelCondition() const;
    void setFuelCondition(float cond);
    void setState(State state);
    void fillFuelTank();
    Road &road;
    const float FUEL_RATIO_ALERT = 0.2f;

private:
    int id;
    std::atomic<float> speed = 0.0f;
    std::thread thread;
    std::mutex mtx;
    std::atomic<long> distance;
    std::atomic<float> fuelCondition;
    std::atomic<State> state = State::DRIVING;
    std::atomic<Direction> direction = Direction::RIGHT;
    std::pair<int,int> downMode(int x, int y);
    std::pair<int,int> leftDownMode(int x, int y, int &counter);
    std::pair<int,int> upMode(int x, int y);
    std::pair<int,int> upPSMode(int x, int y);
    std::pair<int,int> rightMode(int x, int y, int &counter);
    std::pair<int,int> leftMode(int x, int y);
};