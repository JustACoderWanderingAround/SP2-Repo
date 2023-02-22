#pragma once
#include "item.h"
class Inventory
{
public:
	Inventory();
	~Inventory();

	item* headptr;
	item* temp;
	item* findTail();
	std::string items[4];
	std::string descriptions[4];

	item *findName(std::string NAME);
	void addItem(std::string NAME);
	void deleteUsedItem(std::string NAME);


};

