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
        const int BORDER_DOWN = 28;
        const int BORDER_UP = 3;
        const int BORDER_RIGHT = 109;
        const int BORDER_LEFT = 14;
        const int PIT_STOP_BORDER_RIGHT = 132;
        const int COORDS_DIFFERENCE = 2; // less ROWS than COLS
        const int CHANGING_TRACK_BORDER = 85; // to avoid 'crashes'
        const int DOWNTRACK_COORD_X = 36;
        const int UPTRACK_COORD_X = 29;

    private:
        std::pair<int, int> coords[6] = {
            std::make_pair(DOWNTRACK_COORD_X,20), 
            std::make_pair(UPTRACK_COORD_X,20), 
            std::make_pair(DOWNTRACK_COORD_X,30), 
            std::make_pair(UPTRACK_COORD_X,30), 
            std::make_pair(DOWNTRACK_COORD_X,40), 
            std::make_pair(UPTRACK_COORD_X,40)
            };
        std::atomic<bool> race_cont = true;

};