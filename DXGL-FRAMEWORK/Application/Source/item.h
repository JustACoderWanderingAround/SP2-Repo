#ifndef ITEM_H
#define ITEM_H
#include <iostream>
class Item
{
public:
	Item(std::string NAME, std::string DESCRIPTION);
	~Item();

	std::string name;
	int amtOfItems;
	std::string description;
	Item* nextItem;
	Item* prevItem;

	std::string getName();
	int getAmt();
	std::string getDescription();
	Item* getNextItem();
	Item* getPrevItem();

	void addAmt();
	void delAmt();
	void setNextItem(Item* NEXTITEM);
	void setPrevItem(Item* PREVITEM);


};
#endif
