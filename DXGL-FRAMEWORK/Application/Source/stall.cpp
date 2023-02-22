#include "stall.h"

stall::stall()
{
	playerstats->GetInstance();
	highscore = 0;
	coins = playerstats->getCoins();
}

stall::~stall()
{
}

void stall::updateHighscore(int newHS)
{
	highscore = newHS;
}

void stall::updateCoins(int newCoins)
{
	coins = newCoins;
	playerstats->setCoins(newCoins);
}

int stall::getCoins()
{
	return playerstats->getCoins();
}

int stall::getHighscore()
{
	return highscore;
}

void stall::gameplayLoop()
{
}
