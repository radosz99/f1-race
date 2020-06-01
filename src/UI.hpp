#pragma once
#include <array>
#include <thread>
#include <ncurses.h>
#include <mutex>
#include "Bolide.hpp"
#include "Pitstop.hpp"
#include "PitstopManager.hpp"
#include "Storekeeper.hpp"

class UI
{
public:
    UI(const std::array<Bolide, 14>&bolides, Road &road, PitstopManager &pitstopManager, std::array<Storekeeper, 2>&storekeepers);
    ~UI();
    std::mutex change_mutex;
    const std::array<Bolide, 14>& bolides;
    std::array<Storekeeper, 2>&storekeepers;
    PitstopManager &pitstopManager;
    Road &road;

private:
    std::unique_ptr<std::thread> refreshThread;
    std::unique_ptr<std::thread> keyboardThread;
    void refreshView();
    void update();
    void initializeWindow();
    void endVisualisation();
    std::string getProgressBar(float progress, int barLength);
    void destroyWindow(WINDOW* window);
    WINDOW *create_newwin(int height, int width, int starty, int startx);
    WINDOW *bolide1, *bolide2, *bolide3, *bolide4, *bolide5, *bolide6, *bolide7, *bolide8, *bolide9, *bolide10, *bolide11, *bolide12, *bolide13, *bolide14;
    WINDOW *internal_win, *external_win, *pitstop_win, *pit1, *pit2, *pit3, *pit_info1, *pit_info2, *pit_info3;
};