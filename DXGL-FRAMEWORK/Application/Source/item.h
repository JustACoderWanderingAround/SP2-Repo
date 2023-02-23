#ifndef ITEM_H
#define ITEM_H
#include <iostream>
class Item
{
public:
	Item(std::string NAME);
	~Item();

	std::string name;
	int amtOfItems;
	Item* nextItem;
	Item* prevItem;

	std::string getName();
	int getAmt();
	Item* getNextItem();
	Item* getPrevItem();

	void addAmt();
	void delAmt();
	void setNextItem(Item* NEXTITEM);
	void setPrevItem(Item* PREVITEM);


};
#endif
