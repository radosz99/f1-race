#pragma once
#include <string.h>
#include <random>
#include <thread>

class Bolide
{
public:
    Bolide(int x, int y, char dir,  std::string name);
    ~Bolide();
    void run();
    int getX() const;
    int getY() const;
    char getDirection() const;
    std::string getName() const;
    void setDirection(char dir);
    float getFuelCondition() const;
    void setFuelCondition(float cond);

private:
    std::string name;
    float speed = 0.0f;
    int x, y;
    std::thread thread;
    char direction;
    float fuelCondition;
};