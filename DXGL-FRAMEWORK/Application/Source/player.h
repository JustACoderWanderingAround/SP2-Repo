#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
class player
{
	player* instance;
	player();
	int coins;

public:

	void GetInstance();
	int getCoins();
	void setCoins(int newCoins);
	
	
};
#endif

