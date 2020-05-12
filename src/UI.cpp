#include "UI.hpp"

UI::UI(const std::array<Bolide,10>& bolides, Road &road, const std::array<Pitstop, 3>&pitstopes): bolides(bolides), road(road), pitstopes(pitstopes)
{
	initscr();
	cbreak();
    noecho();
    curs_set(0);
	keypad(stdscr, TRUE);
    initializeWindow();
    start_color();
    init_color(COLOR_MAGENTA, 500,300,900);
    init_color(COLOR_RED, 1000,440,0);
    init_pair(1,COLOR_BLUE, COLOR_BLACK);
    wbkgd(stdscr, COLOR_PAIR(1));
    wrefresh(stdscr);
    refreshThread = std::make_unique<std::thread>(&UI::refreshView, this);
    keyboardThread = std::make_unique<std::thread>(&UI::endVisualisation, this);   
}

UI::~UI()
{
    keyboardThread->join();
    refreshThread->join();
    endwin();

}

void UI::destroyWindow(WINDOW* window)
{

	wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(window);
	delwin(window);
}

void UI::initializeWindow()
{
	printw("Press ESC to exit");
    const std::string centerHeader = "F1 Race";
    const std::string rightHeader = "Radoslaw Lis SO2 2019/2020";
    mvprintw(0, COLS - centerHeader.length(), centerHeader.c_str());
    mvprintw(LINES-1, COLS - rightHeader.length(), rightHeader.c_str());
	refresh();
}

void UI::refreshView()
{
    const std::string pitstop1 = "Pit stop 1";
    const std::string pitstop2 = "Pit stop 2";
    const std::string pitstop3 = "Pit stop 3";
    const std::string blank = " ";
    external_win = create_newwin(43, 139, 1, 2);
    internal_win = create_newwin(23, 96, 11, 12 );
    pitstop_win = create_newwin(33, 12, 6, 117);
    pit3 = create_newwin(6, 15, 9, 140);
    pit2 = create_newwin(6, 15, 19, 140);
    pit1 = create_newwin(6, 15, 29, 140);
    pit_info1 = create_newwin(15, 40, 36, 160);
    pit_info2 = create_newwin(15, 40, 19, 160);
    pit_info3 = create_newwin(15, 40, 2, 160);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    wattron(external_win,COLOR_PAIR(8));
    box(external_win,0,0);
    wrefresh (external_win);
    wattroff(external_win,COLOR_PAIR(8));
    wattron(internal_win,COLOR_PAIR(8));
    box(internal_win,0,0);
    wrefresh (internal_win);
    wattroff(internal_win,COLOR_PAIR(8));
    wattron(pitstop_win,COLOR_PAIR(8));
    box(pitstop_win,0,0);
    wrefresh (pitstop_win);
    wattroff(pitstop_win,COLOR_PAIR(8));
    wattron(pit3,COLOR_PAIR(8));
    box(pit3,0,0);
    wrefresh (pit3);
    wattroff(pit3,COLOR_PAIR(8));
    wattron(pit2,COLOR_PAIR(8));
    box(pit2,0,0);
    wrefresh (pit2);
    wattroff(pit2,COLOR_PAIR(8));
    wattron(pit1,COLOR_PAIR(8));
    box(pit1,0,0);
    wrefresh (pit1);
    wattroff(pit1,COLOR_PAIR(8));
    mvprintw(8, 143, pitstop3.c_str());
    mvprintw(18, 143, pitstop2.c_str());
    mvprintw(28, 143, pitstop1.c_str());

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

    while(road.getRaceCont())
    {
        init_color(COLOR_BLUE, 50,600,1000);
	    bolide1 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(0).first,road.getCoords(0).second);
        bolide2 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(1).first,road.getCoords(1).second);
        bolide3 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(2).first,road.getCoords(2).second);
        bolide4 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(3).first,road.getCoords(3).second);
        bolide5 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(4).first,road.getCoords(4).second);
        bolide6 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(5).first,road.getCoords(5).second);
        bolide7 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(6).first,road.getCoords(6).second);
        bolide8 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(7).first,road.getCoords(7).second);
        bolide9 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(8).first,road.getCoords(8).second);
        bolide10 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(9).first,road.getCoords(9).second);

        init_pair(2, COLOR_RED, COLOR_BLACK);
        wattron(bolide1,COLOR_PAIR(2));
        box(bolide1,0,0);
        wrefresh (bolide1);
        wattroff(bolide1,COLOR_PAIR(2));
        init_pair(3, COLOR_CYAN, COLOR_BLACK);
        wattron(bolide2,COLOR_PAIR(3));
        box(bolide2,0,0);
        wrefresh (bolide2);
        wattroff(bolide2,COLOR_PAIR(3));
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        wattron(bolide3,COLOR_PAIR(4));
        box(bolide3,0,0);
        wrefresh (bolide3);
        wattroff(bolide3,COLOR_PAIR(4));
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        wattron(bolide4,COLOR_PAIR(5));
        box(bolide4,0,0);
        wrefresh (bolide4);
        wattroff(bolide4,COLOR_PAIR(5));
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        wattron(bolide5,COLOR_PAIR(6));
        box(bolide5,0,0);
        wrefresh (bolide5);
        wattroff(bolide5,COLOR_PAIR(6));
        init_pair(7, COLOR_BLUE, COLOR_BLACK);
        wattron(bolide6,COLOR_PAIR(2));
        box(bolide6,0,0);
        wrefresh (bolide6);
        wattroff(bolide6,COLOR_PAIR(2));
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        wattron(bolide7,COLOR_PAIR(3));
        box(bolide7,0,0);
        wrefresh (bolide7);
        wattroff(bolide7,COLOR_PAIR(3));
        init_pair(7, COLOR_BLUE, COLOR_BLACK);
        wattron(bolide8,COLOR_PAIR(4));
        box(bolide8,0,0);
        wrefresh (bolide8);
        wattroff(bolide8,COLOR_PAIR(4));
        init_pair(6, COLOR_YELLOW, COLOR_BLACK);
        wattron(bolide9,COLOR_PAIR(5));
        box(bolide9,0,0);
        wrefresh (bolide9);
        wattroff(bolide9,COLOR_PAIR(5));
        init_pair(7, COLOR_BLUE, COLOR_BLACK);
        wattron(bolide10,COLOR_PAIR(6));
        box(bolide10,0,0);
        wrefresh (bolide10);
        wattroff(bolide10,COLOR_PAIR(6));

        refresh();
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        destroyWindow(bolide1);
        destroyWindow(bolide2);
        destroyWindow(bolide3);
        destroyWindow(bolide4);
        destroyWindow(bolide5);
        destroyWindow(bolide6);
        destroyWindow(bolide7);
        destroyWindow(bolide8);
        destroyWindow(bolide9);
        destroyWindow(bolide10);
    }
}

void UI::update()
{
    
    std::string info = "";
    std::string pitstopInfo = "";
    std::string newPitstopInfo(38, ' ');
    const std::string pitstop1 = "Pit stop 1";
    const std::string pitstop2 = "Pit stop 2";
    const std::string pitstop3 = "Pit stop 3";
    const std::string engineer = "Engineers: ";
    const std::string wheel = "Wheels left: ";
    const std::string fuel = "Fuel left: ";
    mvprintw(3, 180 - pitstop3.size()/2, pitstop3.c_str());
    mvprintw(20, 180 - pitstop2.size()/2, pitstop2.c_str());
    mvprintw(37, 180 - pitstop1.size()/2, pitstop1.c_str());
    int shift = 3;
    for(size_t i = 0; i < bolides.size(); i++)
    {
        int colorId = i%5+ 2;
        attron(COLOR_PAIR(colorId));

        info = std::to_string(bolides[i].getId()) + " | " + std::to_string(bolides[i].getOvertaking()) + " | " + std::to_string(bolides[i].getSkill()) + 
                " | " + std::to_string(road.getCoords(i).first) + ", " + std::to_string(road.getCoords(i).second) + " | " + bolides[i].getDirectionString() + " | " + 
                std::to_string(bolides[i].getFailureCounter()) + " | " + std::to_string(bolides[i].getTurbo())  + " | " + std::to_string(bolides[i].getOvertakingCounter()) + 
                 "                  ";

        if(i > 4)
        {
            shift = 74;
        }
        mvprintw(46 + i%5, shift, info.c_str());
        attroff(COLOR_PAIR(colorId));
    }

    for(size_t i = 0; i < pitstopes.size(); i++)
    {
        pitstopInfo = pitstopes[i].getStateString();
        mvprintw(38 - i*17, 161, newPitstopInfo.c_str()); // clear recent info
        attron(COLOR_PAIR(2));
        mvprintw(38 - i*17, 180 - pitstopInfo.size()/2, pitstopInfo.c_str());
        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(7));
        mvprintw(40 - i*17, 161, "1");
        mvprintw(40 - i*17, 162, getProgressBar(1.0).c_str());
        mvprintw(41 - i*17, 161, "2");
        mvprintw(41 - i*17, 162, getProgressBar(0.03).c_str());
        mvprintw(42 - i*17, 161, "3");
        mvprintw(42 - i*17, 162, getProgressBar(0.3).c_str());
        mvprintw(43 - i*17, 161, "4");
        mvprintw(43 - i*17, 162, getProgressBar(0.3).c_str());
        mvprintw(44 - i*17, 161, "f");
        mvprintw(44 - i*17, 162, getProgressBar(0.3).c_str());
        mvprintw(46 - i*17, 161, engineer.c_str());
        mvprintw(47 - i*17, 161, wheel.c_str());
        mvprintw(48 - i*17, 161, fuel.c_str());
        attroff(COLOR_PAIR(7));
    }
}

std::string UI::getProgressBar(float progress)
{
    int barLength = 34;
    std::string finString = " [";
    std::string progressInPercent = std::to_string((int)std::round(progress * 100));
    int lpad = std::round(progress * barLength);
    int rpad = barLength - lpad;
    for(int i = 0; i < lpad; i++)
    {
        finString = finString + "#";
    }
    for(int i = 0; i < rpad; i++)
    {
        finString = finString + " ";
    }
    finString = finString + "]";

    return finString;

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
    while (road.getRaceCont())
    {
        int keyPressed = getch();

        switch (keyPressed)
        {
            case 27: // ESCAPE KEY
                road.setRaceCont(false);
                break;
        }
    }
}
