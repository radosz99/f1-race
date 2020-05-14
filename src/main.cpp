#include <ncurses.h>
#include <string.h>
#include "Bolide.hpp"
#include "TrackManager.hpp"
#include "Storekeeper.hpp"
#include "UI.hpp"

int main(){

	TrackManager trackManager;
	Storekeeper storekeeper(trackManager.getPitstopManager());
    UI ui(trackManager.getBolides(), trackManager.getRoad(), trackManager.getPitstopManager());

	return 0;
}