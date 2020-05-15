#pragma once
#include <atomic>
#include <mutex>
#include <condition_variable>
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
    float getFuelStock() const;
    int getWheelStock() const;
    int getUsedWheels() const;
    void setUsedWheels(int newUsedWheels);
    void setFuelStock(float newFuelStock);
    void setWheelStock(int newWheelStock);
    void setFirstWheelProgress(float progress);
    void setSecondWheelProgress(float progress);
    void setThirdWheelProgress(float progress);
    void setFourthWheelProgress(float progress);
    void setFuelProgress(float progress);
    std::atomic<bool> firstWheelReady = false, secondWheelReady = false, thirdWheelReady = false, fourthWheelReady = false, fuelReady = false; 
    bool firstWheelHandled = false, secondWheelHandled = false, thirdWheelHandled= false, fourthWheelHandled = false, fuelHandled = false; 
    std::mutex firstWheelMtx, secondWheelMtx, thirdWheelMtx, fourthWheelMtx, fuelMtx, wheelStockMtx, fuelStockMtx, waitingForWheelMtx;
    std::atomic<float> fuelNeeded = 0.0f;
    void wait();
	void notify();
    void notifyAll();

private:
    std::condition_variable_any cv;
    std::atomic<PitstopState> status = PitstopState::FREE;
    const int id;
    std::atomic<float> firstWheelProgress = 0.0f;
    std::atomic<float> secondWheelProgress = 0.0f;
    std::atomic<float> thirdWheelProgress = 0.0f;
    std::atomic<float> fourthWheelProgress = 0.0f;
    std::atomic<float> fuelProgress = 0.0f;
    std::atomic<float> fuelStock;
    std::atomic<int> wheelStock;
    std::atomic<int> usedWheels = 0;

};