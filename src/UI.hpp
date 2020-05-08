#pragma once
#include <array>
#include <thread>
#include <ncurses.h>
#include <mutex>
#include "Bolide.hpp"

class UI
{
public:
    UI(const std::array<Bolide, 6>&bolides, Road &road);
    ~UI();
    std::mutex change_mutex;
    const std::array<Bolide, 6>& bolides;
    Road &road;

private:
    int bolideHeight = 4;
    int bolideWidth = 7;
    std::unique_ptr<std::thread> refreshThread;
    std::unique_ptr<std::thread> keyboardThread;
    void refreshView();
    void update();
    void initializeWindow();
    void endVisualisation();
    void destroyWindow(WINDOW* window);
    WINDOW *create_newwin(int height, int width, int starty, int startx);
    WINDOW *bolide1, *bolide2, *bolide3, *bolide4, *bolide5, *bolide6;
    WINDOW *internal_win, *external_win, *pitstop_win, *pit1, *pit2, *pit3;
};