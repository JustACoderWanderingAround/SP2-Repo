
#include "GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>
#include <glm\gtc\matrix_access.hpp>
#include <glm\gtc\epsilon.hpp>
#define ROTATION_SPEED 3.f
GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	multiplier(1.0f / mass),
	timeScale(1.0f)
{
}

GameObject::~GameObject()
{
}

static glm::vec3 RotateVector(const glm::vec3& vec, float radian)
{
	return glm::vec3(vec.x * cos(radian) + vec.y * -sin(radian),
		vec.x * sin(radian) + vec.y * cos(radian), 0.f);
}

bool GameObject::CheckLineCollision(GameObject* go1, GameObject* go2)
{
	glm::vec3 diff = go1->pos - go2->pos;
	glm::vec3 axisX = go2->normal;
	glm::vec3 axisY = glm::vec3(-go2->normal.y, go2->normal.x, 0);

	float projectedDist = dot(diff, axisX);

	if (projectedDist > 0) axisX = -axisX;

	return dot(go1->vel, axisX) >= 0 && //Check 1: Travelling towards the wall ?
		go2->scale.x * 0.5 + go1->scale.x > -dot(diff ,axisX) && //Check 2: Radius + Thickness vs Distance
		go2->scale.y * 0.5 > fabs(dot(diff, axisY)); //Check 3: Length check
}

void GameObject::WallCollisionResponse(GameObject* go1, GameObject* go2)
{
	go1->vel = go1->vel - (2.0f * dot(go1->vel, go2->normal)) * go2->normal;
}

bool GameObject::CheckCSCollision(GameObject* A, GameObject* B)
{
	float distX = fabs(A->pos.y - B->pos.y);
	float distY = fabs(A->pos.x - B->pos.x);

	return !((distX > A->scale.x / 2 + B->scale.x) || (distY > A->scale.y / 2 + B->scale.y));

}

void GameObject::fixedUpdate(double dt)
{
	// check if button press
	slowdown = (glm::all(glm::equal(force, glm::vec3(0))));

	// check if the player is not pressing any button and the object is still moving
	if (slowdown && this->vel != glm::vec3(0)) {
		// add in resistance force to slowly, to simplify the whole equation, you could use -(obj->vel.x)
		// since mass is 1
		if (this->vel.x > 0) {
			force.x = -x_resistant;
		}
		else
			force.x = x_resistant;
	}

	//Calculate the resulting acceleration
	// F = ma.  Hence a = F/M = F * 1/M
	glm::vec3 acc;
	acc = force * multiplier;

	glm::vec3 temp;
	// set initial velocity (U)
	temp = this->vel;

	//commpute the resulting velocity.
	// v = u + at
	this->vel += (float)dt * timeScale * acc;

	// need to check if it's meant to stop the object or not
	// aka check if the player is pressing
	if (slowdown &&
		(this->vel.x > 0 && temp.x < 0) || (this->vel.x < 0 && temp.x > 0))
		this->vel = glm::vec3(0);
	// s = 1/2 (u+v)t
	this->pos += 0.5f * (float)dt * timeScale * (temp + this->vel);

	float angularAcceleration = torque.z / this->momentOfInertia;
	this->anglularVelocity += angularAcceleration * dt;
	this->anglularVelocity = Math::Clamp(this->anglularVelocity, -ROTATION_SPEED, ROTATION_SPEED);

	this->dir = RotateVector(this->dir, this->anglularVelocity * dt);
	// need all the forces to reset
	force = glm::vec3(0);
	torque = glm::vec3(0);
}

bool GameObject::CheckSSCollision(GameObject* B)
{
	// code the collision check here	
	return (glm::distance(this->pos, B->pos) < this->scale.x + B->scale.x);
}

void GameObject::CollisionResponse(GameObject* go2)
{
	// code the collision response here
	glm::vec3 tempgo1 = this->vel;
	glm::vec3 tempgo2 = go2->vel;

	float m1 = this->mass;
	float m2 = go2->mass;

	glm::vec3 mom2 = m2 * tempgo2;
	glm::vec3 mom1 = m1 * tempgo1;

	this->vel = glm::vec3(mom2.x / m1, mom2.y / m1, 0);
	go2->vel = glm::vec3(mom1.x / m2, mom1.y / m2, 0);

	// step 1
	//glm::vec3 normal = glm::vec3(go2->pos.x - this->pos.x, go2->pos.y - this->pos.y, 0);
	glm::vec3 normal = go2->pos - this->pos;
	normal = glm::normalize(normal);
	//std::cout << normal << std::endl;
	//float normalMagnitude = sqrtf((normal.x * normal.x) + (normal.y * normal.y));
	//glm::vec3 unitNormal = normal * (1 / normalMagnitude);
	glm::vec3 unitTangent;
	unitTangent.x = (-1 * normal.y);
	unitTangent.y = (normal.x);
	float normalVel1, normalVel2, tangentVel1, tangentVel2;
	// step 3
	normalVel1 = dot(normal, this->vel);
	normalVel2 = dot(normal, go2->vel);
	tangentVel1 = dot(unitTangent, this->vel);
	tangentVel2 = dot(unitTangent, go2->vel);

	// step 5
	float vNormalVel1, vNormalVel2;
	vNormalVel1 = ((normalVel1 * (this->mass - go2->mass)) + (2 * (go2->mass * normalVel2))) * 1 / (this->mass + go2->mass);
	vNormalVel2 = ((normalVel2 * (go2->mass - this->mass)) + (2 * (this->mass * normalVel1))) * 1 / (this->mass + go2->mass);

	// step 6
	glm::vec3 vPrimeNormalVel1, vPrimeNormalVel2, vPrimeTanVel1, vPrimeTanVel2;

	// v1prime
	vPrimeNormalVel1 = normal * vNormalVel1;
	vPrimeTanVel1 = unitTangent * tangentVel1;

	// v2prime
	vPrimeNormalVel2 = normal * vNormalVel2;
	vPrimeTanVel2 = unitTangent * tangentVel2;

	// step 7
	this->vel = vPrimeNormalVel1 + vPrimeTanVel1;
	go2->vel = vPrimeNormalVel2 + vPrimeTanVel2;

}