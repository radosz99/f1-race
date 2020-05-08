#pragma once
#include <string.h>
#include <random>
#include <atomic>
#include <thread>
#include"Road.hpp"
#include"State.hpp"

class Bolide
{
public:
    Bolide(int x, int y, char dir, int id, Road &road);
    ~Bolide();
    void run();
    std::string getStateString() const;
    int getX() const;
    int getY() const;
    char getDirection() const;
    int getId() const;
    void setDirection(char dir);
    float getFuelCondition() const;
    void setFuelCondition(float cond);
    Road &road;

private:
    int id;
    std::atomic<float> speed = 0.0f;
    int x, y;
    std::thread thread;
    std::atomic<long> distance;
    char direction;
    std::atomic<float> fuelCondition;
    std::atomic<State> state = State::DRIVING;
};