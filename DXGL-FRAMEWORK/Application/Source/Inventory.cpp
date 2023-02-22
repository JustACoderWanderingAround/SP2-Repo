#include "Inventory.h"

Inventory::Inventory()
{
	headptr = nullptr;
	temp = nullptr;
	items[0] = "Zaku Toy";
	items[1] = "Ball";
	items[2] = "Rubik's Cube";
	items[3] = "Potion of Change";
	items[4] = "Cotton Candy";
	items[5] = "Apple";
 
	descriptions[0] = "Robot From Moblie Suit Gundam.";
	descriptions[1] = "A normal ball.";
	descriptions[2] = "3D puzzle.";
	descriptions[3] = "Potion that changes the person's appearance.";
	descriptions[4] = "Candy that melts in the mouth.";
	descriptions[5] = "An apple a day keeps the doctor away.";
}

Inventory::~Inventory()
{
	Item* delItems;
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

Item* Inventory::findTail()
{
	if (headptr == nullptr)
	{
		return nullptr;
	}
	else
	{
		Item* tailptr;
		tailptr = headptr;
		while (tailptr->getNextItem() != nullptr)
		{
			tailptr = tailptr->nextItem;
		}
		return tailptr;
	}
}

Item* Inventory::findName(std::string NAME)
{
	Item* finder;
	finder = headptr;
	while (finder != nullptr)
	{
		if (finder->getName() != NAME)
		{
			finder = finder->nextItem;
		}
		else
		{
			break;
		}
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
	
	if (findName(NAME) != nullptr)
	{
		findName(NAME)->addAmt();
	}
	else 
	{
		// find if name  exist in items[4]
		for (int i = 0; i < 6; i++)
		{
			if (NAME == items[i])
			{
				nameFinder = true;
				desNo = i;
				break;
			}
			else
			{
				nameFinder = false;
			}
		}

		if (nameFinder == true)
		{
			Item* temp2;
			temp = new Item(NAME, descriptions[desNo]);
			if (headptr == nullptr)
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
	
	Item* print;
	print = headptr;
	while (print != nullptr)
	{
		std::cout << print->getName() << print->getAmt() << std::endl;
		print = print->getNextItem();
	}
	print = nullptr;
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
