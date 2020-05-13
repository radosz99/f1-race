#include "TrackManager.hpp"
#include "Pitstop.hpp"
#include "PitstopManager.hpp"

TrackManager::TrackManager()
{
}

TrackManager::~TrackManager()
{
}

const std::array<Bolide, 10> &TrackManager::getBolides() 
{
	return bolides;
}


Road& TrackManager::getRoad()
{
	return road;
}

PitstopManager& TrackManager::getPitstopManager()
{
	return pitstopManager;
}



