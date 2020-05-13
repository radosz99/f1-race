#pragma once
#include <array>
#include <mutex>
#include "Pitstop.hpp"

class PitstopManager
{

public:
    PitstopManager();
    ~PitstopManager();
    std::array<Pitstop, 3> &getPitstopes();
    int getFreePitstop();
    void makePitstop(int pitstopId);

private:
    std::mutex askingMutex;
	std::array<Pitstop, 3> pitstopes
	{
		{
			{ 0 },
			{ 1 },
			{ 2 },
		}
	};

};