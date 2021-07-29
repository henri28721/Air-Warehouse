#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include "item.h"
#include "main_functions.h"
#include "types.h"

using namespace main_functions;

std::string item::ask_name() {
	std::string new_name;
	std::cout << "\n    Give name for item: ";
	getline(std::cin, new_name);
	return new_name;
}
std::string item::ask_pn() {
	std::string new_pn;
	std::cout << "\n    Give part number for item: ";
	getline(std::cin, new_pn);
	return new_pn;
}
std::string item::ask_location() {
	std::string new_location;
	std::cout << "\n    Give location for item: ";
	getline(std::cin, new_location);
	return new_location;
}
std::string item::ask_info() {
	std::string new_info;
	char sel = '-';
	if (std::size(info) > 1) {
		std::cout << "\n    Would you like to replace[r] old information or add[a] to it?: ";
		sel = input_check("ra");
	}
	else {
		sel = 'r';
	}
	std::cout << "\n    Give additional information for item: ";
	switch (sel) {
		case 'r':
			getline(std::cin, new_info);
			break;
		case 'a':
			getline(std::cin, new_info);
			new_info = info + " / " + new_info;
			break;
	}
	return new_info;
}
float item::ask_price() {
	std::string str_price = "";
	float new_price = 0;
	bool go = false;
	std::cout << "\n    Give price for item (per unit): ";
	while (go == false) {
		try {
			getline(std::cin, str_price);
			new_price = std::stof(str_price);
			go = true;
		}
		catch (...) {
			std::cout << "  Invalid input!Try again : ";
		}
	}
	return new_price;
}

std::string item::create_id(char type) {
	std::string zeros = "";
	std::string new_id;
	bool exists = true;
	int count = 1;
	while (exists) {
		int amount_zeros = id_lenght - std::size(std::to_string(count));
		zeros = "";
		for (int i = 0; i < amount_zeros; i++) {
			zeros += '0';
		}
		new_id = zeros + std::to_string(count);
		count++;
		if (std::size(find_by('C', "id", new_id)) < 1) {
			exists = false;
		}
		if (exists == false && std::size(find_by('R', "id", new_id)) > 0) {
			exists = true;
		}
		if (exists == false && std::size(find_by('E', "id", new_id)) > 0) {
			exists = true;
		}
	}
	new_id = type + new_id;
	return new_id;
}

std::string item::ask_expiry_date() {
	char input = '-';
	std::cout << "\n    Does item have expiry date? [y] [n]: ";
	input = input_check("yn");
	std::string new_date = "";
	switch (input) {
		case 'y':
			std::cout << "\n    Give expiry date for item in format (dd.mm.yyyy): ";
			getline(std::cin, new_date);
			break;
		case 'n':
			new_date = "n/a";
	}
	return new_date;
}

float item::ask_amount() {
	std::string str_amount = "";
	float new_amount = 0;
	bool go = false;
	if (id[0] == 'C') std::cout << "\n    Give the amount for item (use \".\" as desimal point): ";
	else if (id[0] == 'E') std::cout << "\n    Give the amount of items (Only whole numbers): ";
	while (go == false) {
		try {
			getline(std::cin, str_amount);
			for (int i = 0; i < std::size(str_amount); i++) {
				if (std::isdigit(str_amount[i]) == false) {
					if (str_amount[i] != '.') throw  std::exception();
				}
			}
			if (id[0] == 'E' && str_amount.find('.') != str_amount.npos) throw std::exception();
			new_amount = std::stof(str_amount);
			go = true;
		}
		catch (...) {
			std::cout << "  Invalid input! Try again: ";
		}
	}
	return new_amount;
}

std::string item::ask_unit() {
	std::string new_unit = "-";
	std::cout << "\n    Give unit for item (In example: pc, l or m): ";
	getline(std::cin, new_unit);
	return new_unit;
}

std::string item::ask_serial() {
	std::string new_serial = "";
	std::cout << "\n    Give serial number or batch number for item: ";
	std::getline(std::cin, new_serial);
	return new_serial;
}

void item::item_info() {
	std::string type_str = "";
	type_str += id[0];
	type_str = char_codes[type_str];
	std::cout   << "	********** " << id << " " << name << " **********\n"
				<< "	           type: " << type_str << '\n'
				<< "	     Partnumber: " << pn << '\n'
				<< "	   Serial/Batch: " << serial << '\n'
				<< "	         Amount: " << amount << " " << unit << '\n'
				<< "	 Price per unit: " << price << '\n'
				<< "	    Expiry date: " << expiry_date << '\n'
				<< "	 Store Location: " << location << '\n'
				<< "	Additional info: " << info << '\n'
		;
}

void item::to_text() {
	std::ofstream file;
	file.open("Items.txt", std::ios_base::app);
	file << "(" << name << "|"
		<< pn << "|" << serial << "|"
		<< amount << "|" << unit << "|"
		<< price << "|" << expiry_date << "|"
		<< location << "|" << id << "|"
		<< info << ")\n";
	file.close();
}

void item::from_list(std::string* item_arr_ptr) {
	name = item_arr_ptr[0];
	pn = item_arr_ptr[1];
	serial = item_arr_ptr[2];
	amount = std::stof(item_arr_ptr[3]);
	unit = item_arr_ptr[4];
	price = std::stof(item_arr_ptr[5]);
	expiry_date = item_arr_ptr[6];
	location = item_arr_ptr[7];
	id = item_arr_ptr[8];
	info = item_arr_ptr[9];
}

void item::save_item() {
	std::string title_text = "FINISHING ITEM CREATION";
	title(title_text);
	char selection = '-';
	std::cout << "    NEW ITEM CREATED: \n\n";
	item_info();
	std::cout << "\n    Do you want to save this item? [Y] [N]: ";
	selection = input_check("yn");
	switch (selection) {
		case 'y':
			to_text();
			title(title_text);
			std::cout << "\n"
				<< "	New item saved. Press [enter] to continue.\n";
			std::cin.ignore();
			return;
		case 'n':
			title(title_text);
			std::cout << "\n"
				<< "	Item creation cancelled. Press [enter] to continue.\n";
			std::cin.ignore();
			return;
	}
}