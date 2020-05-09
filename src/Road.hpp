#pragma once
#include<utility>
#include<mutex>
#include "Direction.hpp"
#include<atomic>

class Road
{
    public:
        Road();
        std::pair<int, int>  getCoords(int index);
        std::pair<int, int>* getAllCoords();
        void setCoords(int index, std::pair<int, int> coord);
        bool checkIfPositionOccupied(int x, int y, Direction direction, int index);
        std::mutex checkMutex;
        void setRaceCont(bool cont);
        bool getRaceCont() const;

    private:
        std::pair<int, int> coords[6] = {std::make_pair(36,20), std::make_pair(29,20), std::make_pair(36,30), std::make_pair(29,30), std::make_pair(36,40), std::make_pair(29,40)};
        std::atomic<bool> race_cont = true;
        int BOLID_WIDTH = 7;
        int BOLID_HEIGHT = 4;
};