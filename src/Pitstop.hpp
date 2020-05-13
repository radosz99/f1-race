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
    float getFirstWheelProgress() const;
    float getSecondWheelProgress() const;
    float getThirdWheelProgress() const;
    float getFourthWheelProgress() const;
    float getFuelProgress() const;
    void setFirstWheelProgress(float progress);
    void setSecondWheelProgress(float progress);
    void setThirdWheelProgress(float progress);
    void setFourthWheelProgress(float progress);
    void setFuelProgress(float progress);

private:
    PitstopState status = PitstopState::FREE;
    std::mutex mtx;
    const int id;
    float firstWheelProgress = 0.0f;
    float secondWheelProgress = 0.0f;
    float thirdWheelProgress = 0.0f;
    float fourthWheelProgress = 0.0f;
    float fuelProgress = 0.0f;

};