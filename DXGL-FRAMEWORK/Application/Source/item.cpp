#include "item.h"

item::item(std::string NAME, std::string DESCRIPTION)
{
	name = NAME;
	amtOfItems = 1;
	description = DESCRIPTION;
	nextItem = nullptr;
	prevItem = nullptr;

}

item::~item()
{
	nextItem = nullptr;
	prevItem = nullptr;
}

std::string item::getName()
{
	return std::string(name);
}

int item::getAmt()
{
	return amtOfItems;
}

std::string item::getDescription()
{
	return std::string(description);
}

item* item::getNextItem()
{
	return nextItem;
}

item* item::getPrevItem()
{
	return prevItem;
}

void item::addAmt()
{
	amtOfItems + 1;
}

void item::delAmt()
{
	amtOfItems - 1;
}

void item::setNextItem(item* NEXTITEM)
{
	nextItem = NEXTITEM;
}

void item::setPrevItem(item* PREVITEM)
{
	prevItem = PREVITEM;
}
