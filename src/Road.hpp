#pragma once
#include<utility>
#include<mutex>

class Road
{
    public:
        Road();
        std::pair<int, int>  getCoords(int index);
        std::pair<int, int>* getAllCoords();
        void setCoords(int index, std::pair<int, int> coord);
        bool checkIfPositionOccupied(int x, int y, char direction, int index);
        std::mutex checkMutex;

    private:
        std::pair<int, int> coords[6] = {std::make_pair(36,20), std::make_pair(29,20), std::make_pair(36,30), std::make_pair(29,30), std::make_pair(36,40), std::make_pair(29,40)};
};