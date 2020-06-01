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
        bool checkIfPositionOccupied(int x, int y, int index);
        std::mutex checkMutex;
        void setRaceCont(bool cont);
        bool getRaceCont() const;
        const int BOLID_WIDTH = 7;
        const int BOLID_HEIGHT = 4;
        const int BORDER_DOWN = 33;
        const int BORDER_UP = 7;
        const int BORDER_RIGHT = 109;
        const int BORDER_LEFT = 4;
        const int PIT_STOP_BORDER_RIGHT = 131;
        const int COORDS_DIFFERENCE = 2; // less ROWS than COLS
        const int CHANGING_PATH_BORDER = 85; // to avoid 'crashes'
        const int DOWN_DOWNPATH_COORD_X = 39;
        const int DOWN_UPPATH_COORD_X = 34;
        const int UP_DOWNPATH_COORD_X = 7;
        const int UP_UPPATH_COORD_X = 2;
        const int PIT_STOP_COORD_X = 30;
        const int PIT_STOP_COORD_Y = 144;

    private:
        std::pair<int, int> coords[14] = {
            std::make_pair(DOWN_DOWNPATH_COORD_X, 5), 
            std::make_pair(DOWN_UPPATH_COORD_X, 5), 
            std::make_pair(DOWN_DOWNPATH_COORD_X, 15), 
            std::make_pair(DOWN_UPPATH_COORD_X, 15), 
            std::make_pair(DOWN_DOWNPATH_COORD_X, 25), 
            std::make_pair(DOWN_UPPATH_COORD_X, 25),
            std::make_pair(DOWN_DOWNPATH_COORD_X, 35),
            std::make_pair(DOWN_UPPATH_COORD_X, 35),
            std::make_pair(DOWN_DOWNPATH_COORD_X, 45), 
            std::make_pair(DOWN_UPPATH_COORD_X, 45),
            std::make_pair(DOWN_DOWNPATH_COORD_X, 55), 
            std::make_pair(DOWN_UPPATH_COORD_X, 55),
            std::make_pair(DOWN_DOWNPATH_COORD_X, 65), 
            std::make_pair(DOWN_UPPATH_COORD_X, 65)
            };
        std::atomic<bool> race_cont = true;

};