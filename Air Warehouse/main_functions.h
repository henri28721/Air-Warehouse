#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "item.h"
#include "types.h"

#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

namespace main_functions {

	static std::map<std::string, std::string> char_codes{
		{"name", "n"},
		{"pn", "p"},
		{"serial", "s"},
		{"amount", "a"},
		{"unit", "u"},
		{"price", "r"},
		{"expiry_date", "e"},
		{"location", "l"},
		{"id", "i"},
		{"info", "f"},
		{"all", "x"},
		{"consumable", "C"},
		{"rotable", "R"},
		{"consumable repairable", "E"},
		{"n", "name"},
		{"p", "pn"},
		{"s", "serial"},
		{"i", "id"},
		{"f", "info"},
		{"C", "consumable"},
		{"R", "rotable"},
		{"E", "consumable repairable"},
	};

	void new_item();
	char input_check(std::string characters);
	void title(std::string text);
	std::vector<int> find_by(char type, std::string property, std::string value);
	void read_file();
	int count_items();
	float count_values();
	std::string to_low(std::string);
	void remove_item(std::string id_to_remove);
	void rewrite_file();
	void reset_vectors();
	
	void debug_print_vectors();
}

#endif
