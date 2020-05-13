#pragma once
#include <array>
#include "Pitstop.hpp"

class PitstopManager
{
public:
    const std::array<Pitstop, 3> &getPitstopes();
private:
	std::array<Pitstop, 3> pitstopes
	{
		{
			{ 0 },
			{ 1 },
			{ 2 },
		}
	};

};