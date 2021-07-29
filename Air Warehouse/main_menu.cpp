#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "main_functions.h"
#include "item.h"
#include "types.h"
#include "main_menu.h"

using namespace main_functions;

extern std::vector<consumable> vec_c;
extern std::vector<rotable> vec_r;
extern std::vector<consumable_repairable> vec_e;
extern bool running;

void main_menu::main_menu() {
	title("MAIN MENU");
	std::cout << "\n" << std::fixed << std::setprecision(2)
		<< "	************************************************\n"
		<< "	Welcome to the aircraft parts warehouse program.\n"
		<< "	Warehouse has currently " << count_items() << " items\n"
		<< "	and has total value of " << count_values() << " euros.\n"
		<< "	************************************************\n\n"
		<< "	[1] ADD ITEM TO THE WAREHOUSE\n\n"
		<< "	[2] REMOVE ITEM FROM THE WAREHOUSE\n\n"
		<< "	[3] SEARCH ITEMS\n\n"
		<< "	[4] EDIT ITEM\n\n"
		<< "	[Q] EXIT PROGRAM\n\n"
		<< "  Selection: ";
	switch (input_check("1234q")) {
		case '1':
			new_item();
			break;
		case '2':
			remove_from_warehouse();
			break;
		case '3':
			search_items();
			break;
		case '4':
			edit_item();
			break;
		case 'q':
			title("MAIN MENU");
			std::cout << "\n"
				<< "	Are you sure you want to quit program? [Y] [N]: ";
			if (input_check("yn") == 'y') {
				running = false;
			}
			return;
	}
}

void main_menu::remove_from_warehouse() {
	std::string string_1 = "";
	std::string string_2 = "";
	char char_1 = '-';
	std::vector<int> found;
	float float_1 = 0;
	int integer_1 = 0;
	case_2_start:
		title("REMOVING ITEM FROM WAREHOUSE");
		std::cout << "\n"
			<< "	Give storage ID of the item to be removed or write \"cancel\": ";
		getline(std::cin, string_1);
		string_1 = to_low(string_1);
		if (string_1 == "cancel") return;
		string_1[0] = std::toupper(string_1[0]);
		switch (string_1[0]) {
			case 'C': // ---------------------------------------------------------- Consumable removal
				found = find_by('C', "id", string_1);
				if (std::size(found) == 1) {
					title("REMOVING CONSUMABLE ITEM FROM WAREHOUSE");
					std::cout << "\n"
						<< "	FOUND ITEM:\n\n";
					vec_c[found[0]].item_info();
					std::cout << "\nGive the amount to be removed or write \"all\" or \"cancel\": ";
					while (float_1 <= 0 || float_1 > vec_c[found[0]].amount) {
						getline(std::cin, string_2);
						for_each(string_2.begin(), string_2.end(), [](char& c) {
							c = tolower(c); });
						if (string_2 == "all" || integer_1 == vec_c[found[0]].amount) {
						all_c:
							title("REMOVING CONSUMABLE ITEM FROM WAREHOUSE");
							std::cout << "\n"
								<< "	Are you sure you want to remove item " << vec_c[found[0]].name << "\n"
								<< "	completely? [Y] or [N]: ";
							switch (input_check("yn")) {
								case 'y':
									remove_item(string_1);
									title("REMOVING CONSUMABLE ITEM FROM WAREHOUSE");
									std::cout << "\n"
										<< "	Item removed. Press [enter] to continue.\n";
									std::cin.ignore();
									return;
									break;
								case 'n':
									title("REMOVING CONSUMABLE ITEM FROM WAREHOUSE");
									std::cout << "\n"
										<< "	Item removal cancelled. Press [enter] to continue.\n";
									std::cin.ignore();
									return;
									break;
							}
						}
						else if (string_2 == "cancel") {
						case_2_cancel:
							title("REMOVING CONSUMABLE ITEM FROM WAREHOUSE");
							std::cout << "\n"
								<< "	Item removal cancelled. Press [enter] to continue.\n";
							std::cin.ignore();
							return;
							break;
						}
						else {
							try {
								float_1 = std::stof(string_2);
								if (float_1 > vec_c[found[0]].amount || float_1 <= 0) throw std::exception();
								if (float_1 == vec_c[found[0]].amount) goto all_c;
								title("REMOVING CONSUMABLE ITEM FROM WAREHOUSE");
								std::cout << "\n"
									<< "	Are you sure you want to remove " << float_1 << " " << vec_c[found[0]].unit << "\n"
									<< "	of " << vec_c[found[0]].name << "? [Y] or [N]: ";
								switch (input_check("yn")) {
									case 'y':
										vec_c[found[0]].amount = vec_c[found[0]].amount - float_1;
										rewrite_file();
										title("REMOVING CONSUMABLE ITEM FROM WAREHOUSE");
										std::cout << "\n"
											<< "	" << float_1 << " " << vec_c[found[0]].unit << " of Item removed." << "\n"
											<< "	" << vec_c[found[0]].amount << " " << vec_c[found[0]].unit << " of " << vec_c[found[0]].name << " left in stock.\n\n"
											<< "	Press[enter] to continue.\n";
										std::cin.ignore();
										return;
										break;
									case 'n':
										goto case_2_cancel;
								}
							}
							catch (...) {
								std::cout << "\n	Invalid value! Try again: ";
							}
						}
					}
				}
				else goto case_2_default;
				break;
			case 'R': // ---------------------------------------------------------- Rotable removal
				found = find_by('R', "id", string_1);
				if (std::size(found) == 1) {
					title("REMOVING ROTABLE ITEM FROM WAREHOUSE");
					std::cout << "\n"
						<< "	FOUND ITEM:\n\n";
					vec_r[found[0]].item_info();
					std::cout << "\n"
						<< "	Are you sure you want to remove item " << vec_r[found[0]].name << "? [Y] or [N]: ";
					switch (input_check("yn")) {
						case 'y':
							remove_item(string_1);
							title("REMOVING ROTABLE ITEM FROM WAREHOUSE");
							std::cout << "\n"
								<< "	Item removed. Press [enter] to continue.\n";
							std::cin.ignore();
							return;
							break;
						case 'n':
							title("REMOVING ROTABLE ITEM FROM WAREHOUSE");
							std::cout << "\n"
								<< "	Item removal cancelled. Press [enter] to continue.\n";
							std::cin.ignore();
							return;
							break;
					}
				}
				else goto case_2_default;
				break;
			case 'E': // ---------------------------------------------------------- Consumable repairable removal
				found = find_by('E', "id", string_1);
				if (std::size(found) == 1) {
					title("REMOVING CONSUMABLE REPAIRABLE ITEM FROM WAREHOUSE");
					std::cout << "\n"
						<< "	FOUND ITEM:\n\n";
					vec_e[found[0]].item_info();
					std::cout << "\nGive the amount to be removed or write \"all\" or \"cancel\": ";
					while (integer_1 <= 0 || integer_1 > vec_e[found[0]].amount) {
						getline(std::cin, string_2);
						for_each(string_2.begin(), string_2.end(), [](char& c) {
							c = tolower(c); });
						if (string_2 == "all" || integer_1 == vec_e[found[0]].amount) {
						all_e:
							title("REMOVING CONSUMABLE REPAIRABLE ITEM FROM WAREHOUSE");
							std::cout << "\n"
								<< "	Are you sure you want to remove item " << vec_e[found[0]].name << "\n"
								<< "	completely? [Y] or [N]: ";
							switch (input_check("yn")) {
								case 'y':
									remove_item(string_1);
									title("REMOVING CONSUMABLE REPAIRABLE ITEM FROM WAREHOUSE");
									std::cout << "\n"
										<< "	Item removed. Press [enter] to continue.\n";
									std::cin.ignore();
									return;
									break;
								case 'n':
									title("REMOVING CONSUMABLE REPAIRABLE ITEM FROM WAREHOUSE");
									std::cout << "\n"
										<< "	Item removal cancelled. Press [enter] to continue.\n";
									std::cin.ignore();
									return;
									break;
							}
						}
						else if (string_2 == "cancel") goto case_2_cancel;
						else {
							try {
								integer_1 = std::stoi(string_2);
								if (integer_1 > vec_e[found[0]].amount || integer_1 <= 0 || string_2.find('.') != string_2.npos) throw std::exception();
								if (integer_1 == vec_e[found[0]].amount) goto all_e;
								title("REMOVING CONSUMABLE REPAIRABLE ITEM FROM WAREHOUSE");
								std::cout << "\n"
									<< "	Are you sure you want to remove " << integer_1 << " " << vec_e[found[0]].unit << "\n"
									<< "	of " << vec_e[found[0]].name << "? [Y] or [N]: ";
								switch (input_check("yn")) {
									case 'y':
										vec_e[found[0]].amount = vec_e[found[0]].amount - integer_1;
										rewrite_file();
										title("REMOVING CONSUMABLE REPAIRABLE ITEM FROM WAREHOUSE");
										std::cout << "\n"
											<< "	" << integer_1 << " " << vec_e[found[0]].unit << " of Item removed." << "\n"
											<< "	" << vec_e[found[0]].amount << " " << vec_e[found[0]].unit << " of " << vec_e[found[0]].name << " left in stock.\n\n"
											<< "	Press[enter] to continue.\n";
										std::cin.ignore();
										return;
										break;
									case 'n':
										goto case_2_cancel;
								}
							}
							catch (...) {
								std::cout << "\n	Invalid value! Try again: ";
							}
						}
					}
				}
				else goto case_2_default;
				break;
			default:
			case_2_default:
				title("REMOVING ITEM FROM WAREHOUSE");
				std::cout << "\n"
					<< "	Item not found. Would you like to try again [Y] or [N]: ";
				char_1 = input_check("yn");
				if (char_1 == 'y') goto case_2_start;
				else return;
		}
}

void main_menu::search_items() {
	char char_1 = '-';
	char char_2 = '-';
	std::string search_word = "";
	std::vector<int> found_vec_c;
	std::vector<int> found_vec_r;
	std::vector<int> found_vec_e;
	int count = 0;
	title("ITEM SEARCH");
	std::cout << "\n"
		<< "	SELECT TYPE OF SEARCH:\n"
		<< "	**********************\n\n"
		<< "	[1] Limit search by type\n\n"
		<< "	[2] Search from all types\n\n"
		<< "	[3] Show all items\n\n"
		<< "	[Q] Exit search\n\n"
		<< "  Selection: ";
	char_1 = input_check("123q");
	switch (char_1) {
		case '1': // ---------------------------------------------------------- Search by type
			title("ITEM SEARCH");
			std::cout << "\n"
				<< "	LIMIT SEARCH BY TYPE\n"
				<< "	********************\n\n"
				<< "	[1] Consumable items\n\n"
				<< "	[2] Rotable items\n\n"
				<< "	[3] Consumable repairable items\n\n"
				<< "	[Q] Exit search\n\n"
				<< "  Selection: ";
			char_1 = input_check("123q");
			if (char_1 != 4) {
				title("ITEM SEARCH");
				std::cout << "\n"
					<< "	LIMIT SEARCH BY TYPE\n"
					<< "	********************\n\n"
					<< "	[1] Search by name\n\n"
					<< "	[2] Search by part number\n\n"
					<< "	[3] Search by serial number\n\n"
					<< "	[4] Search by storage ID\n\n"
					<< "	[5] Search from all information\n\n"
					<< "	[Q] Exit search\n\n"
					<< "  Selection: ";
				char_2 = input_check("12345q");
				if (char_2 == 'q') char_1 = 'q';
				else {
					std::cout << "Give a search word: ";
					getline(std::cin, search_word);
				}
			}
			switch (char_1) {
				case '1': // Consumable
					switch (char_2) {
						case '1': // name
							title("CONSUMABLE ITEM SEARCH BY NAME");
							found_vec_c = find_by('C', "name", search_word);
							break;
						case '2': // pn
							title("CONCUMABLE ITEM SEARCH BY PART NUMBER");
							found_vec_c = find_by('C', "pn", search_word);
							break;
						case '3': // sn
							title("CONSUMABLE ITEM SEARCH BY SERIAL NUMBER");
							found_vec_c = find_by('C', "serial", search_word);
							break;
						case '4': // id
							title("CONSUMABLE ITEM SEARCH BY STORAGE ID");
							found_vec_c = find_by('C', "id", search_word);
							break;
						case '5': // all
							title("CONSUMABLE ITEM SEARCH");
							found_vec_c = find_by('C', "all", search_word);
							break;
					}
					std::cout << "\n"
						<< "	SEARCH RESULTS:\n"
						<< "	***************\n";
					std::cout << "\n    " << std::size(found_vec_c) << " matches found.\n";
					for (int i = 0; i < size(found_vec_c); i++) {
						std::cout << "\n";
						vec_c[found_vec_c[i]].item_info();
					}
					break;
				case '2': // Rotable
					switch (char_2) {
						case '1': // name
							title("ROTABLE ITEM SEARCH BY NAME");
							found_vec_r = find_by('R', "name", search_word);
							break;
						case '2': // pn
							title("ROTABLE ITEM SEARCH BY PART NUMBER");
							found_vec_r = find_by('R', "pn", search_word);
							break;
						case '3': // sn
							title("ROTABLE ITEM SEARCH BY SERIAL NUMBER");
							found_vec_r = find_by('R', "serial", search_word);
							break;
						case '4': // id
							title("ROTABLE ITEM SEARCH BY STORAGE ID");
							found_vec_r = find_by('R', "id", search_word);
							break;
						case '5': // all
							title("ROTABLE ITEM SEARCH");
							found_vec_r = find_by('R', "all", search_word);
							break;
					}
					std::cout << "\n"
						<< "	SEARCH RESULTS:\n"
						<< "	***************\n";
					std::cout << "\n    " << std::size(found_vec_r) << " matches found.\n";
					for (int i = 0; i < size(found_vec_r); i++) {
						std::cout << "\n";
						vec_r[found_vec_r[i]].item_info();
					}
					break;
				case '3': // Consumable repairable
					switch (char_2) {
						case '1': // name
							title("CONSUMABLE REPAIRABLE ITEM SEARCH BY NAME");
							found_vec_e = find_by('E', "name", search_word);
							break;
						case '2': // pn
							title("CONSUMABLE REPAIRABLE SEARCH BY PART NUMBER");
							found_vec_e = find_by('E', "pn", search_word);
							break;
						case '3': // sn
							title("CONSUMABLE REPAIRABLE BY SERIAL NUMBER");
							found_vec_e = find_by('E', "serial", search_word);
							break;
						case '4': // id
							title("CONSUMABLE REPAIRABLE BY STORAGE ID");
							found_vec_e = find_by('E', "id", search_word);
							break;
						case '5': // all
							title("CONSUMABLE REPAIRABLE ITEM SEARCH");
							found_vec_e = find_by('E', "all", search_word);
							break;
					}
					std::cout << "\n"
						<< "	SEARCH RESULTS:\n"
						<< "	***************\n";
					std::cout << "\n    " << std::size(found_vec_e) << " matches found:\n";
					for (int i = 0; i < size(found_vec_e); i++) {
						std::cout << "\n";
						vec_e[found_vec_e[i]].item_info();
					}
					break;
				case 'q': return;
			}
			std::cout << "\n[enter] to exit";
			std::cin.ignore();
			return;
		case '2': // ---------------------------------------------------------- Search from all types
			title("ITEM SEARCH");
			std::cout << "\n"
				<< "	SEARCH FROM ALL TYPES\n"
				<< "	*********************\n\n"
				<< "	[1] Search by name\n\n"
				<< "	[2] Search by part number\n\n"
				<< "	[3] Search by serial number\n\n"
				<< "	[4] Search by storage ID\n\n"
				<< "	[5] Search from all information\n\n"
				<< "	[Q] Exit search\n\n"
				<< "  Selection: ";
			char_1 = input_check("12345q");
			if (char_1 != 'q') {
				std::cout << "Give a search word: ";
				getline(std::cin, search_word);
			}
			switch (char_1) {
				case '1': // name
					title("ITEM SEARCH BY NAME");
					found_vec_c = find_by('C', "name", search_word);
					found_vec_r = find_by('R', "name", search_word);
					found_vec_e = find_by('E', "name", search_word);
					break;
				case '2': // pn
					title("ITEM SEARCH BY PART NUMBER");
					found_vec_c = find_by('C', "pn", search_word);
					found_vec_r = find_by('R', "pn", search_word);
					found_vec_e = find_by('E', "pn", search_word);
					break;
				case '3': // sn
					title("ITEM SEARCH BY SERIAL NUMBER");
					found_vec_c = find_by('C', "sn", search_word);
					found_vec_r = find_by('R', "sn", search_word);
					found_vec_e = find_by('E', "pn", search_word);
					break;
				case '4': // id
					title("ITEM SEARCH BY STORAGE ID");
					found_vec_c = find_by('C', "id", search_word);
					found_vec_r = find_by('R', "id", search_word);
					found_vec_e = find_by('E', "id", search_word);
					break;
				case '5': // all
					title("ITEM SEARCH FROM ALL INFORMATION");
					found_vec_c = find_by('C', "all", search_word);
					found_vec_r = find_by('R', "all", search_word);
					found_vec_e = find_by('E', "all", search_word);
					break;
				case 'q': return;
			}
			std::cout << "\n"
				<< "	SEARCH RESULTS:\n"
				<< "	***************\n";
			count = std::size(found_vec_c) + std::size(found_vec_r) + std::size(found_vec_e);
			std::cout << "\n    " << count << " matches found:\n";
			for (int i = 0; i < size(found_vec_c); i++) {
				std::cout << "\n";
				vec_c[found_vec_c[i]].item_info();
			}
			for (int i = 0; i < size(found_vec_r); i++) {
				std::cout << "\n";
				vec_r[found_vec_r[i]].item_info();
			}
			for (int i = 0; i < size(found_vec_e); i++) {
				std::cout << "\n";
				vec_e[found_vec_e[i]].item_info();
			}
			std::cout << "\n[enter] to exit";
			std::cin.ignore();
			return;
		case '3': // ---------------------------------------------------------- Show all items
			title("ITEM SEARCH");
			std::cout << "\n"
				<< "	SHOW ALL ITEMS\n"
				<< "	**************\n\n"
				<< "	[1] Show all items\n\n"
				<< "	[2] Show all Consumable items\n\n"
				<< "	[3] Show all Rotable items\n\n"
				<< "	[4] Show all Consumable repairable items\n\n"
				<< "	[Q] Exit search\n\n"
				<< "  Selection: ";
			char_1 = input_check("1234q");
			switch (char_1) {
				case '1': // all
					title("ALL ITEMS");
					count = std::size(vec_c) + std::size(vec_r) + std::size(vec_e);
					std::cout << "\n    " << count << " items found:\n";
					std::cout << "\n    CONSUMABLES:\n";
					for (int i = 0; i < std::size(vec_c); i++) {
						std::cout << "\n";
						vec_c[i].item_info();
					}
					std::cout << "\n\n    ROTABLES:\n";
					for (int i = 0; i < std::size(vec_r); i++) {
						std::cout << "\n";
						vec_r[i].item_info();
					}
					std::cout << "\n\n    CONSUMABLE REPAIRABLES:\n";
					for (int i = 0; i < std::size(vec_e); i++) {
						std::cout << "\n";
						vec_e[i].item_info();
					}
					break;
				case '2': // All consumable
					title("ALL CONSUMABLE ITEMS");
					std::cout << "\n    " << std::size(vec_c) << " items found:\n";
					for (int i = 0; i < std::size(vec_c); i++) {
						std::cout << "\n";
						vec_c[i].item_info();
					}
					break;
				case '3': // All rotable
					title("ALL ROTABLE ITEMS");
					std::cout << "\n    " << std::size(vec_r) << " items found:\n";
					for (int i = 0; i < std::size(vec_r); i++) {
						std::cout << "\n";
						vec_r[i].item_info();
					}
					break;
				case '4': // All consumable repairable
					title("ALL CONSUMABLE REPAIRABLE ITEMS");
					std::cout << "\n    " << std::size(vec_e) << " items found:\n";
					for (int i = 0; i < std::size(vec_e); i++) {
						std::cout << "\n";
						vec_e[i].item_info();
					}
					break;
				case 'q': return;
			}
			std::cout << "\n[enter] to exit";
			std::cin.ignore();
			return;
		case 'q': return;
	}
}

void main_menu::edit_item() {
	std::string title_text = "EDITING ITEM";
	bool ask = true;
	std::string storage_id = "";
	int index = 0;
	while (ask) {
		title(title_text);
		std::cout << "\n"
			<< "	Give storage ID of the item to be edited or write \"cancel\": ";
		getline(std::cin, storage_id);
		storage_id = to_low(storage_id);
		if (storage_id == "cancel") return;
		storage_id[0] = toupper(storage_id[0]);
		switch (storage_id[0]) {
			case 'C':
				for (int i = 0; i < std::size(vec_c); i++) {
					if (vec_c[i].id == storage_id) {
						index = i;
						ask = false;
					}
				}
				if (ask) goto default_case;
				break;
			case 'R':
				for (int i = 0; i < std::size(vec_r); i++) {
					if (vec_r[i].id == storage_id) {
						index = i;
						ask = false;
					}
				}
				if (ask) goto default_case;
				break;
			case 'E':
				for (int i = 0; i < std::size(vec_e); i++) {
					if (vec_e[i].id == storage_id) {
						index = i;
						ask = false;
					}
				}
				if (ask) goto default_case;
				break;
			default:
				default_case:
				title(title_text);
				std::cout << "\n"
					<< "	Item not found. Would you like to try again [Y] or [N]: ";
				if (input_check("yn") == 'n') return;
		}
	}
	editing_item:
	title(title_text);
	std::cout << "\n"
		<< "	FOUND ITEM:\n\n";
	switch (storage_id[0]) {
		case 'C': vec_c[index].item_info(); break;
		case 'R': vec_r[index].item_info(); break;
		case 'E': vec_e[index].item_info(); break;
	}
	std::cout << "\n"
		<< "	CHOOSE VALUE TO EDIT:\n"
		<< "	*********************\n\n"
		<< "	[1] Name\n\n"
		<< "	[2] Part number\n\n"
		<< "	[3] Serial number\n\n"
		<< "	[4] Amount\n\n"
		<< "	[5] Unit\n\n"
		<< "	[6] Price\n\n"
		<< "	[7] Expiry date\n\n"
		<< "	[8] Location\n\n"
		<< "	[9] Info\n\n"
		<< "	[Q] Cancel edit\n\n"
		<< "  Selection: ";
	switch (input_check("123456789q")) {
		case '1':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].name = vec_c[index].ask_name(); break;
				case 'R': vec_r[index].name = vec_r[index].ask_name(); break;
				case 'E': vec_e[index].name = vec_e[index].ask_name(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item name changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '2':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].pn = vec_c[index].ask_pn(); break;
				case 'R': vec_r[index].pn = vec_r[index].ask_pn(); break;
				case 'E': vec_e[index].pn = vec_e[index].ask_pn(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item part number changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '3':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].serial = vec_c[index].ask_serial(); break;
				case 'R': vec_r[index].serial = vec_r[index].ask_serial(); break;
				case 'E': vec_e[index].serial = vec_e[index].ask_serial(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item serial/batch number changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '4':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].amount = vec_c[index].ask_amount(); break;
				case 'R': vec_r[index].amount = vec_r[index].ask_amount(); break;
				case 'E': vec_e[index].amount = vec_e[index].ask_amount(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item amount changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '5':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].unit = vec_c[index].ask_unit(); break;
				case 'R': vec_r[index].unit = vec_r[index].ask_unit(); break;
				case 'E': vec_e[index].unit = vec_e[index].ask_unit(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item unit changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '6':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].price = vec_c[index].ask_price(); break;
				case 'R': vec_r[index].price = vec_r[index].ask_price(); break;
				case 'E': vec_e[index].price = vec_e[index].ask_price(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item price changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '7':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].expiry_date = vec_c[index].ask_expiry_date(); break;
				case 'R': vec_r[index].expiry_date = vec_r[index].ask_expiry_date(); break;
				case 'E': vec_e[index].expiry_date = vec_e[index].ask_expiry_date(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item expiry date changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '8':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].location = vec_c[index].ask_location(); break;
				case 'R': vec_r[index].location = vec_r[index].ask_location(); break;
				case 'E': vec_e[index].location = vec_e[index].ask_location(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item location changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case '9':
			title(title_text);
			switch (storage_id[0]) {
				case 'C': vec_c[index].info = vec_c[index].ask_info(); break;
				case 'R': vec_r[index].info = vec_r[index].ask_info(); break;
				case 'E': vec_e[index].info = vec_e[index].ask_info(); break;
			}
			rewrite_file();
			title(title_text);
			std::cout << "\n"
				<< "	Item information changed. Do you want to continue editing item? [Y] [N]: ";
			break;
		case 'q': return;
	}
	if (input_check("yn") == 'y') {
		goto editing_item;
	}
	return;
}