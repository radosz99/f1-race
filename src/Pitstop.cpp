#include "Pitstop.hpp"
#include "PitstopState.hpp"
#include "Random.hpp"

//TODO: add engineer thread with skill atribute and others needed
Pitstop::Pitstop(int id) : id(id)
{
    fuelStock = static_cast<float> (static_cast<float>(Random().randomInt(50,100))/10);
    wheelStock = Random().randomInt(15,20);
}

PitstopState Pitstop::getStatus() const
{
    return status;
}

void Pitstop::wait()
{
	std::unique_lock<std::mutex> lock(waitingForWheelMtx);
	cv.wait(lock);
}

void Pitstop::notify()
{
    std::unique_lock<std::mutex> lock(waitingForWheelMtx);
	cv.notify_one();
}


void Pitstop::notifyAll()
{
    std::unique_lock<std::mutex> lock(waitingForWheelMtx);
	cv.notify_all();
}


void Pitstop::setStatus(PitstopState newStatus)
{
    status = newStatus;
}

int Pitstop::getId() const
{
    return id;
}

std::string Pitstop::getStateString() const
{

    switch (status)
    {
        case PitstopState::FREE:
            return "FREE";
        case PitstopState::BUSY:
            return "BUSY";
        case PitstopState::WAITING_FOR_BOLIDE:
            return "WAITING_FOR_BOLIDE";
    }
}

float Pitstop::getFirstWheelProgress() const
{
    return firstWheelProgress;
}

float Pitstop::getSecondWheelProgress() const
{
    return secondWheelProgress;
}

float Pitstop::getThirdWheelProgress() const
{
    return thirdWheelProgress;
}

float Pitstop::getFourthWheelProgress() const
{
    return fourthWheelProgress;
}

float Pitstop::getFuelProgress() const
{
    return fuelProgress;
}

float Pitstop::getFuelStock() const
{
    return fuelStock;
}

int Pitstop::getWheelStock() const
{
    return wheelStock;
}

int Pitstop::getUsedWheels() const
{
    return usedWheels;
}


void Pitstop::setFuelStock(float newFuelStock)
{
    fuelStock = newFuelStock;
}

void Pitstop::setWheelStock(int newWheelStock)
{
    wheelStock = newWheelStock;
}

void Pitstop::setUsedWheels(int newUsedWheels)
{
    usedWheels = newUsedWheels;
}


void Pitstop::setFirstWheelProgress(float progress)
{
    firstWheelProgress = progress;
}

void Pitstop::setSecondWheelProgress(float progress)
{
    secondWheelProgress = progress;
}

void Pitstop::setThirdWheelProgress(float progress)
{
    thirdWheelProgress = progress;
}

void Pitstop::setFourthWheelProgress(float progress)
{
    fourthWheelProgress = progress;
}

void Pitstop::setFuelProgress(float progress)
{
    fuelProgress = progress;
}
