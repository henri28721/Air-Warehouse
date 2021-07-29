#include <iostream>
#include <string>
#include <vector>

#include "main_functions.h"
#include "item.h"
#include "types.h"
#include "main_menu.h"

using namespace main_functions;

// There is three types of items: Consumable (c), Rotable (r) and Consumable repairable (e).
// Consumable: Consumable items like tapes and fuilds.
// Rotable: Items that after using can be returned to service after overhaul.
// Consumable repairable: Parts that will be discarded after usage.

std::vector<consumable> vec_c;
std::vector<rotable> vec_r;
std::vector<consumable_repairable> vec_e;
bool running;

int main() {
	//program setup:
	read_file();
	running = true;

	//program run:
	while (running) {
		main_menu::main_menu();
	}
}