#pragma once
#include "item.h"
class Inventory
{
public:
	Inventory();
	~Inventory();

	Item* headptr;
	Item* temp;
	Item* findTail();
	std::string items[6];
	std::string descriptions[6];

	Item*findName(std::string NAME);
	void addItem(std::string NAME);



};

