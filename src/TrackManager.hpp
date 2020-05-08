#pragma once
#include <array>
#include <mutex>
#include "Bolide.hpp"
#include "Road.hpp"

class TrackManager
{
public:

    TrackManager();
    ~TrackManager();
    const std::array<Bolide, 6> &getBolides();
	Road road;
	Road &getRoad();

private:
	std::array<Bolide, 6> bolides
	{
	   {
			{ 36, 20, 'r', 0, road},
			{ 29, 20, 'r', 1, road},
			{ 36, 30, 'r', 2, road},
			{ 29, 30, 'r', 3, road},
			{ 36, 40, 'r', 4, road},
			{ 29, 40, 'r', 5, road},
		  }
	};

};
