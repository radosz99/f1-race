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
                if(!pitstop.fuelReady && !pitstop.fuelHandled)
                {
                    if(pitstop.fuelMtx.try_lock())
                    {
                        activity = 0;
                        pitstop.fuelHandled = true;
                        doActivity(0);
                        pitstop.fuelReady = true;
                        activity = -1;
                        pitstop.fuelStockMtx.lock();
                        pitstop.setFuelStock(pitstop.getFuelStock()-pitstop.fuelNeeded);
                        pitstop.fuelNeeded = 0.0f;
                        pitstop.fuelStockMtx.unlock();
                        pitstop.fuelMtx.unlock();
                    }
                }
                if(!pitstop.firstWheelReady && !pitstop.firstWheelHandled)
                {
                    if(pitstop.firstWheelMtx.try_lock())
                    {
                        activity = 1;
                        pitstop.firstWheelHandled = true;
                        doActivity(1);
                        pitstop.firstWheelReady = true;
                        activity = -1;
                        pitstop.wheelStockMtx.lock();
                        pitstop.setWheelStock(pitstop.getWheelStock()-1);
                        pitstop.wheelStockMtx.unlock();
                        pitstop.firstWheelMtx.unlock();
                    }
                }

                if(!pitstop.secondWheelReady && !pitstop.secondWheelHandled)
                {
                    if(pitstop.secondWheelMtx.try_lock())
                    {
                        activity = 2;
                        pitstop.secondWheelHandled = true;
                        doActivity(2);
                        pitstop.secondWheelReady = true;
                        activity = -1;
                        pitstop.wheelStockMtx.lock();
                        pitstop.setWheelStock(pitstop.getWheelStock()-1);
                        pitstop.wheelStockMtx.unlock();
                        pitstop.secondWheelMtx.unlock();
                    }
                }

                if(!pitstop.thirdWheelReady && !pitstop.thirdWheelHandled)
                {
                    if(pitstop.thirdWheelMtx.try_lock())
                    {
                        activity = 3;
                        pitstop.thirdWheelHandled = true;
                        doActivity(3);
                        pitstop.thirdWheelReady = true;
                        activity = -1;
                        pitstop.wheelStockMtx.lock();
                        pitstop.setWheelStock(pitstop.getWheelStock()-1);
                        pitstop.wheelStockMtx.unlock();
                        pitstop.thirdWheelMtx.unlock();
                    }
                }

                if(!pitstop.fourthWheelReady && !pitstop.fourthWheelHandled)
                {
                    if(pitstop.fourthWheelMtx.try_lock())
                    {
                        activity = 4;
                        pitstop.fourthWheelHandled = true;
                        doActivity(4);
                        pitstop.fourthWheelReady = true;
                        activity = -1;
                        pitstop.wheelStockMtx.lock();
                        pitstop.setWheelStock(pitstop.getWheelStock()-1);
                        pitstop.wheelStockMtx.unlock();
                        pitstop.fourthWheelMtx.unlock();
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(600));
            pitstop.setStatus(PitstopState::FREE);
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
        }
    }
}

void Engineer::doActivity(int id)
{
    int delayCount = 150 - 80*skill;

	for (int i = 1; i <= delayCount; i++)
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
}

int Engineer::getSkill() const
{
    return static_cast<int>(skill * 100);
}