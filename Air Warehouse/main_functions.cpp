#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <map>
#include <algorithm>
#include <fstream>

#include "main_functions.h"
#include "item.h"
#include "types.h"

using namespace main_functions;

#define title_width 80 // How many charactes wide title is. 

extern std::vector<consumable> vec_c;
extern std::vector<rotable> vec_r;
extern std::vector<consumable_repairable> vec_e;

void main_functions::new_item() { // Chooses right assembler for item.
	std::string input = "";
	int item_count = count_items();
	title("CREATING NEW ITEM");
	std::cout << "\n"
		<< "	SELECT TYPE OF NEW ITEM:\n"
		<< "	************************\n\n"
		<< "	[1] Consumable\n\n"
		<< "	[2] Rotable\n\n"
		<< "	[3] Consumable repairable\n\n"
		<< "	[Q] Cancel item creation\n\n"
		<< "  Selection: ";
	char new_type = input_check("123q");
	switch (new_type) {
		case '1': // Consumable
			vec_c.push_back(consumable());
			break;
		case '2': // Rotable
			vec_r.push_back(rotable());
			break;
		case '3': // Consumable repairable
			vec_e.push_back(consumable_repairable());
			break;
		case 'q': return;
	}
	if (item_count == count_items()) reset_vectors();
}

char main_functions::input_check(std::string characters) { // Asks input that is one of characters in string.
	std::string character = "";
	std::string input = "";
	while (true) {
		getline(std::cin, input);
		input[0] = tolower(input[0]);
		for (unsigned int i = 0; i < std::size(characters); i++) {
			character = characters[i];
			if (character == input) return input[0];
		}
		std::cout << "Wrong input. Try again: ";
	}
}

void main_functions::title(std::string text) { //clears console and generates title from given text.
	int title_size = std::size(text);
	double amount_a = floor((title_width - title_size) / 2);
	double amount_b = ceil((title_width - title_size) / 2);
	std::string line_top = "";
	std::string line_separator = "";
	std::string text_a = "";
	std::string text_b = "";
	for (int i = 0; i < title_width; i++) {
		line_top += '*';
		line_separator += '_';
	}
	line_separator += "_____";
	for (int i = 0; i < amount_a; i++) {
		text_a += ' ';
	}
	for (int i = 0; i < amount_b; i++) {
		text_b += ' ';
	}
	std::cout << "\n" << line_separator << "\n\n\n\n\n\n\n\n\n\n";
	std::cout << line_top << '\n' << text_a << text << text_b << '\n' << line_top << "\n\n";
}


// Finds item with given input: Type(c,r,x), property and value. Returns vector containing indexes that matches value.
std::vector<int> main_functions::find_by(char type, std::string property_str, std::string value) {
	value = to_low(value);
	int index_size = 0;
	std::vector<int> found;
	std::string word = "";
	switch (type) {
		case 'C':
			index_size = std::size(vec_c);
			switch (char_codes[property_str][0]) {
				case 'n':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_c[index].name);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'p':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_c[index].pn);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 's':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_c[index].serial);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'i':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_c[index].id);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'f':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_c[index].info);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'x':
					for (int index = 0; index < index_size; index++) {
						if (std::find(found.begin(), found.end(), index) == found.end()) {
							word = to_low(vec_c[index].name);
							if (word.find(value) < word.npos) found.push_back(index);
							else {
								word = to_low(vec_c[index].pn);
								if (word.find(value) < word.npos) found.push_back(index);
								else {
									word = to_low(vec_c[index].serial);
									if (word.find(value) < word.npos) found.push_back(index);
									else {
										word = to_low(vec_c[index].id);
										if (word.find(value) < word.npos) found.push_back(index);
										else {
											word = to_low(vec_c[index].info);
											if (word.find(value) < word.npos) found.push_back(index);
										}
									}
								}
							}
						}
					}
					break;
			}
			break;
		case 'R':
			index_size = std::size(vec_r);
			switch (char_codes[property_str][0]) {
				case 'n':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_r[index].name);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'p':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_r[index].pn);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 's':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_r[index].serial);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'i':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_r[index].id);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'f':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_r[index].info);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'x':
					for (int index = 0; index < index_size; index++) {
						if (std::find(found.begin(), found.end(), index) == found.end()) {
							word = to_low(vec_r[index].name);
							if (word.find(value) < word.npos) found.push_back(index);
							else {
								word = to_low(vec_r[index].pn);
								if (word.find(value) < word.npos) found.push_back(index);
								else {
									word = to_low(vec_r[index].serial);
									if (word.find(value) < word.npos) found.push_back(index);
									else {
										word = to_low(vec_r[index].id);
										if (word.find(value) < word.npos) found.push_back(index);
										else {
											word = to_low(vec_r[index].info);
											if (word.find(value) < word.npos) found.push_back(index);
										}
									}
								}
							}
						}
					}
			}
			break;
		case 'E':
			index_size = std::size(vec_e);
			switch (char_codes[property_str][0]) {
				case 'n':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_e[index].name);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'p':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_e[index].pn);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 's':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_e[index].serial);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'i':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_e[index].id);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'f':
					for (int index = 0; index < index_size; index++) {
						word = to_low(vec_e[index].info);
						if (word.find(value) < word.npos) found.push_back(index);
					}
					break;
				case 'x':
					for (int index = 0; index < index_size; index++) {
						if (std::find(found.begin(), found.end(), index) == found.end()) {
							word = to_low(vec_e[index].name);
							if (word.find(value) < word.npos) found.push_back(index);
							else {
								word = to_low(vec_e[index].pn);
								if (word.find(value) < word.npos) found.push_back(index);
								else {
									word = to_low(vec_e[index].serial);
									if (word.find(value) < word.npos) found.push_back(index);
									else {
										word = to_low(vec_e[index].id);
										if (word.find(value) < word.npos) found.push_back(index);
										else {
											word = to_low(vec_e[index].info);
											if (word.find(value) < word.npos) found.push_back(index);
										}
									}
								}
							}
						}
					}
			}
			break;
	}
	return found;
}

void main_functions::debug_print_vectors() { // For making sure vectors works correctly
	int c_size = std::size(vec_c);
	int r_size = std::size(vec_r);
	int e_size = std::size(vec_e);
	std::cout << "Item count: " << count_items() << "\n";
	std::cout << "vec_c size : " << std::size(vec_c) << "\n";
	std::cout << "vec_r size : " << std::size(vec_r) << "\n";
	std::cout << "vec_e size : " << std::size(vec_e) << "\n";
	std::cout << "\nConsumables:\n";
	for (int i = 0; i < c_size; i++) {
		std::cout << vec_c[i].name << ", ";
	}
	std::cout << "\n\nRotables:\n";
	for (int i = 0; i < r_size; i++) {
		std::cout << vec_r[i].name << ", ";
	}
	std::cout << "\n\nConsumable Repairables:\n";
	for (int i = 0; i < e_size; i++) {
		std::cout << vec_e[i].name << ", ";
	}
	std::cout << "\n";
}

void main_functions::read_file() { // Reads file ands items to program
	std::ifstream file("Items.txt");
	std::string line = "";
	std::string word = "";
	char type = '-';
	std::string id = "";
	std::string item_arr[10];
	std::string* item_arr_ptr = item_arr;
	bool read = false;
	int line_size;
	int item_index = 0;
	while (getline(file, line)) {
		line_size = std::size(line);
		for (int i = 0; i < line_size; i++) {
			switch (line[i]) {
				case '(':
					read = true;
					break;
				case ')':
					read = false;
					item_arr[item_index] = word;
					word = "";
					item_index = 0;
					id = item_arr[8];
					type = id[0];
					switch (type) {
						case 'C':
							vec_c.push_back(consumable(item_arr_ptr));
							break;
						case 'R':
							vec_r.push_back(rotable(item_arr_ptr));
							break;
						case 'E':
							vec_e.push_back(consumable_repairable(item_arr_ptr));
							break;
					}
					for (int i = 0; i < 9; i++) {
						item_arr[i] = "";
					}
					break;
				case '|':
					item_arr[item_index] = word;
					word = "";
					item_index++;
					break;
				default:
					if (read) {
						word += line[i];
					}
			}
		}
	}
	file.close();
}

int main_functions::count_items() { // Counts items in file.
	std::ifstream file("Items.txt");
	std::string line = "";
	int count = 0;
	while (getline(file, line)) {
		if (std::size(line) > 15) {
			count++;
		}
	}
	file.close();
	return count;
}

float main_functions::count_values() { // Counts total value of warehouse.
	float total_value = 0;
	for (unsigned int i = 0; i < std::size(vec_c); i++) {
		total_value = total_value + (vec_c[i].price * vec_c[i].amount);
	}
	for (unsigned int i = 0; i < std::size(vec_r); i++) {
		total_value = total_value + (vec_r[i].price * vec_r[i].amount);
	}
	for (unsigned int i = 0; i < std::size(vec_e); i++) {
		total_value = total_value + (vec_e[i].price * vec_e[i].amount);
	}
	return total_value;
}

std::string main_functions::to_low(std::string word) { // String to lowercase.
	for_each(word.begin(), word.end(), [](char& c) {
		c = tolower(c); });
	return word;
}

void main_functions::remove_item(std::string id_to_remove) { // Removes item from warehouse.
	std::ifstream file_read("Items.txt");
	std::string line = "";
	std::vector<std::string> file_vec;
	int spacer_count = 0;
	std::string id_read = "";
	while (getline(file_read, line)) {
		for (unsigned int i = 0; i < std::size(line); i++) {
			if (line[i] == '|') {
				spacer_count++;
			}
			else if (spacer_count == 8) {
				id_read += line[i];
			}
		}
		if (id_read != id_to_remove) {
			file_vec.push_back(line);
		}
		spacer_count = 0;
		id_read = "";
	}
	file_read.close();
	std::ofstream file_write;
	file_write.open("Items.txt", std::ofstream::out | std::ofstream::trunc);
	for (unsigned int i = 0; i < std::size(file_vec); i++) {
		file_write << file_vec[i] << "\n";
	}
	file_write.close();
	reset_vectors();
}

void main_functions::rewrite_file() { // Clears file and writes vectors to file.
	std::ofstream file_write;
	file_write.open("Items.txt", std::ofstream::out | std::ofstream::trunc);
	file_write.close();
	for (unsigned int i = 0; i < std::size(vec_c); i++) {
		vec_c[i].to_text();
	}
	for (unsigned int i = 0; i < std::size(vec_r); i++) {
		vec_r[i].to_text();
	}
	for (unsigned int i = 0; i < std::size(vec_e); i++) {
		vec_e[i].to_text();
	}
}

void main_functions::reset_vectors() { // Clears vectors and reads file again.
	vec_c.clear();
	vec_r.clear();
	vec_e.clear();
	read_file();
}