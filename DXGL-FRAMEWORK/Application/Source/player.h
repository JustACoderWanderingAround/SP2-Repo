#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
class Player
{
public:
	static Player* GetInstance(void);
	void DestroyInstance(void);
	int getCoins();
	void setCoins(int newCoins);
	int coins;
	glm::vec3 playerPos;
	glm::vec3 getPos();
	void setPos(glm::vec3 currentPos);


private:

	Player(void);
	~Player(void);
	static Player* instance;

};
#endif

