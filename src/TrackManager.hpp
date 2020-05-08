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
			{ 0, road},
			{ 1, road},
			{ 2, road},
			{ 3, road},
			{ 4, road},
			{ 5, road},
		  }
	};

};
