#pragma once
#include <array>
#include <mutex>
#include "Bolide.hpp"
#include "Road.hpp"
#include "Pitstop.hpp"

class TrackManager
{
public:

    TrackManager();
    ~TrackManager();
    const std::array<Bolide, 6> &getBolides();
	const std::array<Pitstop, 3> &getPitstopes();
	Road road;
	Road &getRoad();

private:
	std::array<Pitstop, 3> pitstopes
	{
		{
			{ 0 },
			{ 1 },
			{ 2 },
		}
	};

	std::array<Bolide, 6> bolides
	{
	   {
			{ 0, road, pitstopes},
			{ 1, road, pitstopes},
			{ 2, road, pitstopes},
			{ 3, road, pitstopes},
			{ 4, road, pitstopes},
			{ 5, road, pitstopes},
		  }
	};

};
