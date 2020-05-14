#include <ncurses.h>
#include <string.h>
#include "Bolide.hpp"
#include "TrackManager.hpp"
#include "UI.hpp"

int main(){

	TrackManager trackManager;
	//std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    UI ui(trackManager.getBolides(), trackManager.getRoad(), trackManager.getPitstopManager(), trackManager.getStorekeepers());

	return 0;
}