#include "Engineer.hpp"
#include "Random.hpp"

Engineer::Engineer(int id, int pitstopId):id(id), pitstopId(pitstopId),thread(&Engineer::run, this)
{
    skill = static_cast<float> (static_cast<float>(Random().randomInt(20,90))/100);
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

    }
}

void Engineer::setRaceCont(bool value)
{
    raceCont = value;
}