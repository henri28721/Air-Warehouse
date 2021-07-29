#include <iostream>
#include <string>

#ifndef ITEM_H
#define ITEM_H

#define id_lenght 5 //Lenght of id code.

class item {
public:
	std::string name;			 // Name of the item.	
	std::string pn;				 // Manufacturer part number.
	std::string serial;			 // Serial or batch number for item.
	float amount;				 // Amount of item units.
	std::string unit;			 // Unit wich item is handled with.
	float price;				 // price per unit (total/amount)
	std::string expiry_date;	 // Expiry date for item.
	std::string location;		 // Shelf where item is located.
	std::string id;				 // storage identification code
	std::string info;			 // Additional information about item.
	
	// Asks new values from user
	std::string ask_name();
	std::string ask_pn();
	std::string ask_serial();
	float ask_amount();
	std::string ask_unit();
	float ask_price();
	std::string ask_expiry_date();
	std::string ask_location();
	std::string ask_info();

	std::string create_id(char type); //Creates id for item based on it's type.
	void item_info(); // Prints information about item.
	void to_text(); // Adds item to items.txt.
	void from_list(std::string* item_arr_ptr); //Adds information to item from list.
	void save_item(); // Ask if created items is saved.
};

#endif