#ifndef STALL_H
#define STALL_H
#include "player.h"

class stall
{
public:
	int highscore;
	int coins;
	player * playerstats;

	stall();
	~stall();

	void updateHighscore(int newHS);
	void updateCoins(int newCoins);
	int getCoins();
	int getHighscore();
	virtual void gameplayLoop();

};
#endif

