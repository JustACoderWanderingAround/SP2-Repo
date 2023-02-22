#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
class player
{
public:
	static player* GetInstance(void);
	void DestroyInstance(void);
	int getCoins();
	void setCoins(int newCoins);
	int coins;
	glm::vec3 playerPos;
	glm::vec3 getPos();
	void setPos(glm::vec3 currentPos);


private:

	player(void);
	~player(void);
	static player* instance;

};
#endif

