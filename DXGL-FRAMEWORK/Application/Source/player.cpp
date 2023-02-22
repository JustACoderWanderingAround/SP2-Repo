#include "player.h"

player* player::instance = nullptr;

player::player(void)
{
	coins = 0;
}

player::~player(void)
{
}

player* player::GetInstance(void)
{
	if (instance == nullptr)
	{
		instance = new player();
	}
	return instance;
}

void player::DestroyInstance(void)
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
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

glm::vec3 player::getPos()
{
	return glm::vec3(playerPos);
}

void player::setPos(glm::vec3 currentPos)
{
	playerPos = currentPos;
}

