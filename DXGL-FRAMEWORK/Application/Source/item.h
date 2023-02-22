#ifndef ITEM_H
#define ITEM_H
#include <iostream>
class item
{
public:
	item(std::string NAME, std::string DESCRIPTION);
	~item();

	std::string name;
	int amtOfItems;
	std::string description;
	item* nextItem;
	item* prevItem;

	std::string getName();
	int getAmt();
	std::string getDescription();
	item* getNextItem();
	item* getPrevItem();

	void addAmt();
	void delAmt();
	void setNextItem(item* NEXTITEM);
	void setPrevItem(item* PREVITEM);


};
#endif
