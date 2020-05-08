#pragma once
#include "TrackManager.hpp"
class TrackSetup
{
    public:
        TrackSetup(const TrackManager &manager);
        const TrackManager &manager;

    private:
};