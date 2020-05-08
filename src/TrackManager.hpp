#pragma once
#include <array>
#include <mutex>
#include "Bolide.hpp"

class TrackManager
{
public:

    TrackManager();
    ~TrackManager();
    std::mutex checkMutex;
    bool checkIfPositionOccupied(int x, int y, char direction);
    const std::array<Bolide, 6> &getBolides();

private:
    TrackSetup setup;
	std::array<Bolide, 6> bolides
	{
	   {
			{ 37, 20, 'r', "A" },
			{ 32, 20, 'r', "B" },
			{ 37, 30, 'r', "C" },
			{ 32, 30, 'r', "D" },
			{ 37, 40, 'r', "E" },
			{ 32, 40, 'r', "F" },
		  }
	};

};