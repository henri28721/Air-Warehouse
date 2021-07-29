#include <iostream>
#include <string>

#include "item.h"


#ifndef TYPES_H
#define TYPES_H 

class consumable : public item {
public:
	const char type = 'C';
	consumable();
	consumable(std::string *item_arr_ptr);
	~consumable();
};

class rotable : public item {
public:
	const char type = 'R';
	rotable();
	rotable(std::string* item_arr_ptr);
	~rotable();
};

class consumable_repairable : public item {
public:
	const char type = 'E';
	consumable_repairable();
	consumable_repairable(std::string* item_arr_ptr);
	~consumable_repairable();
};

#endif
