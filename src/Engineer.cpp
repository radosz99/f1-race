#include "Engineer.hpp"
#include "Random.hpp"
#include "Pitstop.hpp"
#include <iostream>

Engineer::Engineer(int id, Pitstop &pitstop):id(id), pitstop(pitstop),thread(&Engineer::run, this)
{
    skill = static_cast<float> (static_cast<float>(Random().randomInt(20,100))/100);
    raceCont = true;
}

Engineer::~Engineer()
{
    std::cout << "Engineer end" << std::endl;
    thread.join();
}

void Engineer::run()
{
    while(raceCont)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(pitstop.getStatus()==PitstopState::BUSY)
        {
            while(!pitstop.fuelReady || !pitstop.firstWheelReady|| !pitstop.secondWheelReady || !pitstop.thirdWheelReady || !pitstop.fourthWheelReady)
            {
                if(!pitstop.firstWheelReady && !pitstop.firstWheelHandled)
                {
                    if(pitstop.firstWheelMtx.try_lock())
                    {
                        activity = 1;
                        pitstop.firstWheelHandled = true;
                        if(pitstop.getWheelStock() <= 0)
                        {
                            pitstop.wait();
                        }
                        pitstop.setWheelStock(pitstop.getWheelStock() - 1);
                        pitstop.setUsedWheels(pitstop.getUsedWheels() + 1);
                        doActivity(1);
                        pitstop.firstWheelReady = true;
                        activity = -1;
                        pitstop.firstWheelMtx.unlock();
                    }
                }

                if(!pitstop.secondWheelReady && !pitstop.secondWheelHandled)
                {
                    if(pitstop.secondWheelMtx.try_lock())
                    {
                        activity = 2;
                        pitstop.secondWheelHandled = true;
                        if(pitstop.getWheelStock() <= 0)
                        {
                            pitstop.wait();
                        }
                        pitstop.setWheelStock(pitstop.getWheelStock() - 1);
                        pitstop.setUsedWheels(pitstop.getUsedWheels() + 1);
                        doActivity(2);
                        pitstop.secondWheelReady = true;
                        activity = -1;
                        pitstop.secondWheelMtx.unlock();
                    }
                }

                if(!pitstop.thirdWheelReady && !pitstop.thirdWheelHandled)
                {
                    if(pitstop.thirdWheelMtx.try_lock())
                    {
                        activity = 3;
                        pitstop.thirdWheelHandled = true;
                        if(pitstop.getWheelStock() <= 0)
                        {
                            pitstop.wait();
                        }
                        pitstop.setWheelStock(pitstop.getWheelStock() - 1);
                        pitstop.setUsedWheels(pitstop.getUsedWheels() + 1);
                        doActivity(3);
                        pitstop.thirdWheelReady = true;
                        activity = -1;
                        pitstop.thirdWheelMtx.unlock();
                    }
                }

                if(!pitstop.fourthWheelReady && !pitstop.fourthWheelHandled)
                {
                    if(pitstop.fourthWheelMtx.try_lock())
                    {
                        activity = 4;
                        pitstop.fourthWheelHandled = true;
                        if(pitstop.getWheelStock() <= 0)
                        {
                            pitstop.wait();
                        }
                        pitstop.setWheelStock(pitstop.getWheelStock() - 1);
                        pitstop.setUsedWheels(pitstop.getUsedWheels() + 1);
                        doActivity(4);
                        pitstop.fourthWheelReady = true;
                        activity = -1;
                        pitstop.fourthWheelMtx.unlock();
                    }
                }

                if(!pitstop.fuelReady && !pitstop.fuelHandled)
                {
                    if(pitstop.fuelMtx.try_lock())
                    {
                        activity = 0;
                        pitstop.fuelHandled = true;
                        pitstop.setFuelStock(pitstop.getFuelStock() - pitstop.fuelNeeded);
                        pitstop.fuelNeeded = 0.0f;
                        doActivity(0);
                        pitstop.fuelReady = true;
                        activity = -1;
                        pitstop.fuelMtx.unlock();
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            pitstop.setFuelProgress(0);
            pitstop.setFirstWheelProgress(0);
            pitstop.setSecondWheelProgress(0);
            pitstop.setThirdWheelProgress(0);
            pitstop.setFourthWheelProgress(0);
            pitstop.fuelReady = false;
            pitstop.firstWheelReady = false;
            pitstop.secondWheelReady = false;
            pitstop.thirdWheelReady = false;
            pitstop.fourthWheelReady = false;
            pitstop.fuelHandled = false;
            pitstop.firstWheelHandled= false;
            pitstop.secondWheelHandled= false;
            pitstop.thirdWheelHandled= false;
            pitstop.fourthWheelHandled = false;
            pitstop.wait();
            pitstop.setStatus(PitstopState::FREE);
        }
    }
}

void Engineer::doActivity(int id)
{
    int delayCount = 120 - 80 * skill;

	for (int i = 1; i <= delayCount && raceCont; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
        switch(id)
        {
		    case 0:
                pitstop.setFuelProgress(static_cast<float>(i) / static_cast<float>(delayCount));
                break;
            case 1:
                pitstop.setFirstWheelProgress(static_cast<float>(i) / static_cast<float>(delayCount));
                break;
            case 2:
                pitstop.setSecondWheelProgress(static_cast<float>(i) / static_cast<float>(delayCount));
                break;
            case 3:
                pitstop.setThirdWheelProgress(static_cast<float>(i) / static_cast<float>(delayCount));
                break;
            case 4:
                pitstop.setFourthWheelProgress(static_cast<float>(i) / static_cast<float>(delayCount));
                break;
        }
    }
}
void Engineer::setRaceCont(bool value)
{
    raceCont = value;
    pitstop.notifyAll();
}

int Engineer::getSkill() const
{
    return static_cast<int>(skill * 100);
}
