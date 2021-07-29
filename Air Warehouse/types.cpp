#include <iostream>
#include <string>

#include "types.h"
#include "main_functions.h";

using namespace main_functions;

consumable::consumable(): item() {
	std::string title_text = "CREATING NEW CONSUMABLE ITEM";
	id = create_id(type);
	title(title_text);
	name = ask_name();
	title(title_text);
	pn = ask_pn();
	title(title_text);
	serial = ask_serial();
	title(title_text);
	unit = ask_unit();
	title(title_text);
	amount = ask_amount();
	title(title_text);
	expiry_date = ask_expiry_date();
	title(title_text);
	location = ask_location();
	title(title_text);
	price = ask_price();
	title(title_text);
	info = ask_info();
	save_item();
};

consumable::consumable(std::string* item_arr_ptr) : item() {
	item::from_list(item_arr_ptr);
}

consumable::~consumable() {}

rotable::rotable(): item() {
	std::string title_text = "CREATING NEW ROTABLE ITEM";
	id = create_id(type);
	title(title_text);
	name = ask_name();
	title(title_text);
	pn = ask_pn();
	title(title_text);
	serial = ask_serial();
	unit = "pc";
	amount = 1; // There can be only one rotable per serial number.
	title(title_text);
	expiry_date = ask_expiry_date();
	title(title_text);
	location = ask_location();
	title(title_text);
	price = ask_price();
	title(title_text);
	info = ask_info();
	save_item();
};

rotable::rotable(std::string* item_arr_ptr) : item() {
	item::from_list(item_arr_ptr);
}

rotable::~rotable() {}

consumable_repairable::consumable_repairable(): item() {
	std::string title_text = "CREATING NEW CONSUMABLE REPAIRABLE ITEM";
	id = create_id(type);
	title(title_text);
	name = ask_name();
	title(title_text);
	pn = ask_pn();
	title(title_text);
	serial = ask_serial();
	title(title_text);
	unit = "pc"; // Only "pc" is allowable unit for consumable repaireable item.
	title(title_text);
	amount = ask_amount();
	title(title_text);
	expiry_date = ask_expiry_date();
	title(title_text);
	location = ask_location();
	title(title_text);
	price = ask_price();
	title(title_text);
	info = ask_info();
	save_item();
};

consumable_repairable::consumable_repairable(std::string* item_arr_ptr) : item() {
	item::from_list(item_arr_ptr);
}

consumable_repairable::~consumable_repairable() {}
