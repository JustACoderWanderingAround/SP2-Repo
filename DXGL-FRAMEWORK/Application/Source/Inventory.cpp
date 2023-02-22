#include "Inventory.h"

Inventory::Inventory()
{
	headptr = nullptr;
	temp = nullptr;
	items[0] = "Zaku Toy";
	items[1] = "Ball";
	items[2] = "Rubik's Cube";
	items[3] = "Potion of Change";

	descriptions[0] = "Robot From Moblie Suit Gundam.";
	descriptions[1] = "A normal ball.";
	descriptions[2] = "3D puzzle.";
	descriptions[3] = "Potion that changes the person's appearnce";
}

Inventory::~Inventory()
{
	item* delItems;
	delItems = headptr;
	while (delItems != nullptr)
	{
		headptr = delItems->getNextItem(); // make head point to next node
		delete delItems;
		delItems = headptr;
	}
	headptr = nullptr;
	temp = nullptr;
}

item* Inventory::findTail()
{
	if (headptr == nullptr)
	{
		return nullptr;
	}
	else
	{
		item* tailptr;
		tailptr = headptr;
		while (tailptr->getNextItem() != nullptr)
		{
			tailptr = tailptr->nextItem;
		}
		return tailptr;
	}
}

item* Inventory::findName(std::string NAME)
{
	item* finder;
	finder = headptr;
	while (finder->getName() != NAME && finder->getNextItem() != nullptr
		&& finder != nullptr)
	{
		// check next one when the prev is not NAME and and next is Not nullptr 
		finder = finder->nextItem;
	}

	return finder;
}

void Inventory::addItem(std::string NAME)
{
	
	bool nameFinder;
	int desNo;
	nameFinder = false;
	desNo = 0;
	// find name in LL
	
	if (findName(NAME)->name == NAME)
	{
		findName(NAME)->addAmt();
	}
	else
	{
		// find if name  exist in items[4]
		for (int i = 0; i < 4; i++)
		{
			if (NAME == items[i])
			{
				nameFinder = true;
				desNo = 1;
				break;
			}
			else
			{
				nameFinder = false;
			}
		}

		if (nameFinder == true)
		{
			item* temp2;
			temp = new item(NAME, descriptions[desNo]);
			if (findName(NAME) == nullptr)
			{
				headptr = temp;
			}
			else
			{
				temp2 = findTail();
				temp2->setNextItem(temp);
				temp->setPrevItem(temp2);
				
			}
			temp2 = nullptr;
			temp = nullptr;
		}
		else
		{
			// dont do anything
			std::cout << "does not exist!" << std::endl;
		}
		
	}
	
}

void Inventory::deleteUsedItem(std::string NAME)
{
	
	if (findName(NAME)->getName() == NAME)
	{
		findName(NAME)->delAmt();
	}
	else
	{
		// it does not exist 
		std::cout << "does not exist" << std::endl;
	}
}
