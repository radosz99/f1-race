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

	// std::array<Engineer, 9> engineers
	// {
	// 	{
	// 		{ 0, 0 },
	// 		{ 1, 0 },
	// 		{ 2, 0 },
	// 		{ 3, 1 },
	// 		{ 4, 1 },
	// 		{ 5, 1 },
	// 		{ 6, 2 },
	// 		{ 7, 2 },
	// 		{ 8, 2 },
	// 	}
	// };

};