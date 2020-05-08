#include "TrackManager.hpp"

TrackManager::TrackManager()
{
}

TrackManager::~TrackManager()
{
}

const std::array<Bolide, 6> &TrackManager::getBolides() 
{
	return bolides;
}

Road& TrackManager::getRoad()
{
	return road;
}


