#include "TrackManager.hpp"
#include "Pitstop.hpp"
#include "PitstopManager.hpp"
#include "Storekeeper.hpp"

TrackManager::TrackManager()
{
}

TrackManager::~TrackManager()
{
}

const std::array<Bolide, 14> &TrackManager::getBolides() 
{
	return bolides;
}

std::array<Storekeeper, 2> &TrackManager::getStorekeepers()
{
	return storekeepers;
}


Road& TrackManager::getRoad()
{
	return road;
}

PitstopManager& TrackManager::getPitstopManager()
{
	return pitstopManager;
}



