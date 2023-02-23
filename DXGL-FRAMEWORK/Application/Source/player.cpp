#include "player.h"

Player* Player::instance = nullptr;

Player::Player(void)
{
	coins = 0;
	playerPos = glm::vec3(0, -7, -40);
}

Player::~Player(void)
{

}

Player* Player::GetInstance(void)
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

void Player::DestroyInstance(void)
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

int Player::getCoins()
{
	return coins;
}

void Player::setCoins(int newCoins)
{
	coins = newCoins;
}

glm::vec3 Player::getPos()
{
	return glm::vec3(playerPos);
}

void Player::setPos(glm::vec3 currentPos)
{
	playerPos = currentPos;
}

