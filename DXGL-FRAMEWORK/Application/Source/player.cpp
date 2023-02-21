#include "player.h"

void player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new player;
	}
}

int player::getCoins()
{
	return coins;
}

void player::setCoins(int newCoins)
{
	coins = newCoins;
}

player::player()
{
	coins = 0;
	instance = nullptr;
}
