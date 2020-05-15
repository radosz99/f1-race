#pragma once
#include <array>
#include <mutex>
#include "Pitstop.hpp"
#include "Road.hpp"
#include "Engineer.hpp"

class PitstopManager
{

public:
    PitstopManager();
    ~PitstopManager();
    std::array<Pitstop, 3> &getPitstopes();
	std::array<Engineer, 9> &getEngineers();
    int getFreePitstop();
    void makePitstop(int pitstopId, float fuelCondition);
	void setRaceCont(bool newRaceCont);


private:
	std::atomic<bool>raceCont = true;
    std::mutex askingMutex;
	std::array<Pitstop, 3> pitstopes
	{
		{
			{ 0 },
			{ 1 },
			{ 2 },
		}
	};

	std::array<Engineer, 9> engineers
	{
		{
			{ 0, pitstopes[0] },
			{ 1, pitstopes[0] },
			{ 2, pitstopes[0] },
			{ 3, pitstopes[1] },
			{ 4, pitstopes[1] },
			{ 5, pitstopes[1] },
			{ 6, pitstopes[2] },
			{ 7, pitstopes[2] },
			{ 8, pitstopes[2] },
		}
	};

};