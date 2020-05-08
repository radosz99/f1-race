#include <ncurses.h>
#include <string.h>
#include "Bolide.hpp"
#include "TrackManager.hpp"
#include "UI.hpp"

int main(){

	TrackManager trackManager;
    UI ui(trackManager.getBolides());

	return 0;
}