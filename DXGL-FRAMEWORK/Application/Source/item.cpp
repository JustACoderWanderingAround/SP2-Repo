#include "Item.h"

Item::Item(std::string NAME)
{
	name = NAME;
	amtOfItems = 1;
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
