#include"Pitstop.hpp"
#include"PitstopState.hpp"

//TODO: add engineer thread with skill atribute and others needed
Pitstop::Pitstop(int id) : id(id)
{

}
PitstopState Pitstop::getStatus() const
{
    return status;
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
