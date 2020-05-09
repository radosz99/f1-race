#include "UI.hpp"

UI::UI(const std::array<Bolide,6>& bolides, Road &road):bolides(bolides), road(road)
{
	initscr();
	cbreak();
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
    // destroyWindow(bolide1);
    // destroyWindow(bolide2);
    // destroyWindow(bolide3);
    // destroyWindow(bolide4);
    // destroyWindow(bolide5);
    // destroyWindow(bolide6);
    // delwin(bolide1);
    // delwin(bolide2);
    // delwin(bolide3);
    // delwin(bolide4);
    // delwin(bolide5);
    // delwin(bolide6);
    // destroyWindow(internal_win);
    // destroyWindow(external_win);
    // destroyWindow(pitstop_win);
    // destroyWindow(pit1);
    // destroyWindow(pit2);
    // destroyWindow(pit3);
    // delwin(internal_win);
    // delwin(external_win);
    // delwin(pitstop_win);
    // delwin(pit1);
    // delwin(pit2);
    // delwin(pit3);
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
    external_win = create_newwin(40, 129, 2, 12);
    internal_win = create_newwin(21, 86, 7, 22 );
    pitstop_win = create_newwin(28, 12, 8, 117);
    pit3 = create_newwin(6, 15, 9, 140);
    pit2 = create_newwin(6, 15, 19, 140);
    pit1 = create_newwin(6, 15, 29, 140);
    init_pair(8,COLOR_WHITE, COLOR_BLACK);
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

    while(road.getRaceCont())
    {
        init_color(COLOR_BLUE, 50,600,1000);
	    bolide1 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(0).first,road.getCoords(0).second);
        bolide2 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(1).first,road.getCoords(1).second);
        bolide3 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(2).first,road.getCoords(2).second);
        bolide4 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(3).first,road.getCoords(3).second);
        bolide5 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(4).first,road.getCoords(4).second);
        bolide6 = create_newwin(BOLID_HEIGHT, BOLID_WIDTH, road.getCoords(5).first,road.getCoords(5).second);

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
        wattron(bolide6,COLOR_PAIR(7));
        box(bolide6,0,0);
        wrefresh (bolide6);
        wattroff(bolide6,COLOR_PAIR(7));

        refresh();
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(280));
        destroyWindow(bolide1);
        destroyWindow(bolide2);
        destroyWindow(bolide3);
        destroyWindow(bolide4);
        destroyWindow(bolide5);
        destroyWindow(bolide6);
    }
}

void UI::update()
{
    std::string info="";
    for(size_t i=0; i<bolides.size(); i++)
    {
        attron(COLOR_PAIR(i+2));
        info = std::to_string(bolides[i].getId()) + " ma jeszcze paliwa " + std::to_string(bolides[i].getFuelCondition()) + 
        " a koordynaty " + std::to_string(road.getCoords(i).first) + " i " + std::to_string(road.getCoords(i).second) + " i " + bolides[i].getStateString() + " i " + 
        bolides[i].getDirectionString() + "                              ";
        mvprintw(45+i, 3, info.c_str());
        attroff(COLOR_PAIR(i+2));
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