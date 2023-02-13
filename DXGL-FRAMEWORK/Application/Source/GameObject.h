#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "MyMath.h"
#include "Vector3.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_access.hpp>
#define x_resistant 3

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_TEXT,
		GO_BALL,
		GO_CUBE,
		GO_BULLET,
		GO_WALL,
		GO_ALIEN,  // aliens
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 normal;
	Vector3 force;
	Vector3 dir;
	Vector3 torque;
	bool slowdown;
	int timeScale;
	void fixedUpdate(double dt);
	bool CheckSSCollision(GameObject* A, GameObject* B);
	void CollisionResponse(GameObject* go1, GameObject* go2);
	bool CheckLineCollision(GameObject* go1, GameObject* go2);
	void WallCollisionResponse(GameObject* go1, GameObject* go2);
	bool CheckCSCollision(GameObject* A, GameObject* B);
	bool active;
	float mass;
	float momentOfInertia;
	float anglularVelocity;
	float multiplier;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();
};
#endif

