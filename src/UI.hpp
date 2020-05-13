#pragma once
#include <array>
#include <thread>
#include <ncurses.h>
#include <mutex>
#include "Bolide.hpp"
#include "Pitstop.hpp"
#include "PitstopManager.hpp"

class UI
{
public:
    UI(const std::array<Bolide, 10>&bolides, Road &road, PitstopManager &pitstopManager);
    ~UI();
    std::mutex change_mutex;
    const std::array<Bolide, 10>& bolides;
    PitstopManager &pitstopManager;
    Road &road;

private:
    std::unique_ptr<std::thread> refreshThread;
    std::unique_ptr<std::thread> keyboardThread;
    void refreshView();
    void update();
    void initializeWindow();
    void endVisualisation();
    std::string getProgressBar(float progress);
    void destroyWindow(WINDOW* window);
    WINDOW *create_newwin(int height, int width, int starty, int startx);
    WINDOW *bolide1, *bolide2, *bolide3, *bolide4, *bolide5, *bolide6, *bolide7, *bolide8, *bolide9, *bolide10;
    WINDOW *internal_win, *external_win, *pitstop_win, *pit1, *pit2, *pit3, *pit_info1, *pit_info2, *pit_info3;
};