#pragma once
#include <array>
#include <mutex>
#include "Bolide.hpp"
#include "Road.hpp"
#include "Pitstop.hpp"
#include "PitstopManager.hpp"
#include "Storekeeper.hpp"

class TrackManager
{
public:

    TrackManager();
    ~TrackManager();
    const std::array<Bolide, 14> &getBolides();
	std::array<Storekeeper, 2> &getStorekeepers();
	Road road;
	Road &getRoad();
	PitstopManager &getPitstopManager();

private:
	PitstopManager pitstopManager;
	

	std::array<Bolide, 14> bolides
	{
	   {
			{ 0, road, pitstopManager},
			{ 1, road, pitstopManager},
			{ 2, road, pitstopManager},
			{ 3, road, pitstopManager},
			{ 4, road, pitstopManager},
			{ 5, road, pitstopManager},
			{ 6, road, pitstopManager},
			{ 7, road, pitstopManager},
			{ 8, road, pitstopManager},
			{ 9, road, pitstopManager},
			{ 10, road, pitstopManager},
			{ 11, road, pitstopManager},
			{ 12, road, pitstopManager},
			{ 13, road, pitstopManager},
		  }
	};

	std::array<Storekeeper, 2> storekeepers
	{
		{
			{pitstopManager.getPitstopes()},
			{pitstopManager.getPitstopes()},
		}
	};

};
