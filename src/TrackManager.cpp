#include "TrackManager.hpp"
#include "Pitstop.hpp"
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

const std::array<Pitstop, 3> &TrackManager::getPitstopes() 
{
	return pitstopes;
}


Road& TrackManager::getRoad()
{
	return road;
}


