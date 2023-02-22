#include "Item.h"

Item::Item(std::string NAME, std::string DESCRIPTION)
{
	name = NAME;
	amtOfItems = 1;
	description = DESCRIPTION;
	nextItem = nullptr;
	prevItem = nullptr;

}

Item::~Item()
{
	nextItem = nullptr;
	prevItem = nullptr;
}

std::string Item::getName()
{
	return std::string(name);
}

int Item::getAmt()
{
	return amtOfItems;
}

std::string Item::getDescription()
{
	return std::string(description);
}

Item* Item::getNextItem()
{
	return nextItem;
}

Item* Item::getPrevItem()
{
	return prevItem;
}

void Item::addAmt()
{
	amtOfItems += 1;
}

void Item::delAmt()
{
	amtOfItems -= 1;
}

void Item::setNextItem(Item* NEXTITEM)
{
	nextItem = NEXTITEM;
}

void Item::setPrevItem(Item* PREVITEM)
{
	prevItem = PREVITEM;
}
