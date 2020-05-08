#include "UI.hpp"

UI::UI(const std::array<Bolide,6>& bolides):bolides(bolides)
{
	int ch=10;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
    initializeWindow();

    refreshThread = std::make_unique<std::thread>(&UI::refreshView, this);
    keyboardThread = std::make_unique<std::thread>(&UI::endVisualisation, this);   
}

UI::~UI()
{
    keyboardThread->join();
    refreshThread->join();
}

void UI::destroyWindow(WINDOW* window)
{
	wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(window);
	delwin(window);
}

void UI::initializeWindow()
{
    race_cont = true;
    int startx, starty, width, height;
	height = 4;
	width = 7;
	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;
	printw("Press ESC to exit");
    const std::string centerHeader = "F1 Race";
    const std::string rightHeader = "Radoslaw Lis SO2 2019/2020";
    const std::string pitstop1 = "Pit stop 1";
    const std::string pitstop2 = "Pit stop 2";
    const std::string pitstop3 = "Pit stop 3";
    const std::string blank = " ";
    const std::string a = "A";
    mvprintw(0, COLS - centerHeader.length(), centerHeader.c_str());
    mvprintw(LINES-1, COLS - rightHeader.length(), rightHeader.c_str());
	refresh();
    external_win = create_newwin(40, 129, 2, 12);
    internal_win = create_newwin(20, 70, 12, 30 );
    //up_road = create_newwin(38, 24, 3, 117);
    down_road = create_newwin(28, 12, 8, 117);
    pit1 = create_newwin(6, 15, 9, 140);
    pit2 = create_newwin(6, 15, 19, 140);
    pit3 = create_newwin(6, 15, 29, 140);
    mvprintw(8, 143, pitstop1.c_str());
    mvprintw(18, 143, pitstop2.c_str());
    mvprintw(28, 143, pitstop3.c_str());
    mvprintw(40, 117, blank.c_str());
    mvprintw(39, 117, blank.c_str());
    mvprintw(38, 117, blank.c_str());
    mvprintw(37, 117, blank.c_str());
    mvprintw(36, 117, blank.c_str());
    mvprintw(7, 117, blank.c_str());
    mvprintw(6, 117, blank.c_str());
    mvprintw(5, 117, blank.c_str());
    mvprintw(4, 117, blank.c_str());
    mvprintw(3, 117, blank.c_str());
    mvprintw(11, 140, blank.c_str());
    mvprintw(12, 140, blank.c_str());
    mvprintw(13, 140, blank.c_str());
    mvprintw(14, 140, blank.c_str());
    mvprintw(9, 140, blank.c_str());
    mvprintw(10, 140, blank.c_str());
    mvprintw(21, 140, blank.c_str());
    mvprintw(22, 140, blank.c_str());
    mvprintw(23, 140, blank.c_str());
    mvprintw(24, 140, blank.c_str());
    mvprintw(19, 140, blank.c_str());
    mvprintw(20, 140, blank.c_str());
    mvprintw(31, 140, blank.c_str());
    mvprintw(32, 140, blank.c_str());
    mvprintw(33, 140, blank.c_str());
    mvprintw(34, 140, blank.c_str());
    mvprintw(29, 140, blank.c_str());
    mvprintw(30, 140, blank.c_str());
    move(50, 0);
}

void UI::refreshView()
{
    while(race_cont==true)
    {
        destroyWindow(bolide1);
        destroyWindow(bolide2);
        destroyWindow(bolide3);
        destroyWindow(bolide4);
        destroyWindow(bolide5);
        destroyWindow(bolide6);
	    bolide1 = create_newwin(4, 7, bolides[0].getX(),bolides[0].getY());
        bolide2 = create_newwin(4, 7, bolides[1].getX(),bolides[1].getY());
        bolide3 = create_newwin(4, 7, bolides[2].getX(),bolides[2].getY());
        bolide4 = create_newwin(4, 7, bolides[3].getX(),bolides[3].getY());
        bolide5 = create_newwin(4, 7, bolides[4].getX(),bolides[4].getY());
        bolide6 = create_newwin(4, 7, bolides[5].getX(),bolides[5].getY());
        refresh();
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void UI::update()
{
    std::string info="";
    for(size_t i=0; i<bolides.size(); i++)
    {
        info = bolides[i].getName() + " ma jeszcze paliwa " + std::to_string(bolides[i].getFuelCondition());
        mvprintw(45+i, 3, info.c_str());
    }
}

WINDOW *UI::create_newwin(int height, int width, int starty, int startx)
{	
    WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
	wrefresh(local_win);

	return local_win;
}

void UI::endVisualisation()
{
    while (true)
    {
        int keyPressed = getch();

        switch (keyPressed)
        {
            case 27: // ESCAPE KEY
                race_cont = false;
                endwin();
                break;
        }
    }
}