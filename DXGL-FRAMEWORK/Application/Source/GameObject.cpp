#include "MyMath.h"
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
void GameObject::setDirection(const glm::vec3& vec, float radian) {
	this->dir = RotateVector(vec, radian);
}

bool GameObject::CheckLineCollision(GameObject* that)
{
	glm::vec3 diff = this->pos - that->pos;
	glm::vec3 axisX = that->normal;
	glm::vec3 axisY = glm::vec3(-that->normal.y, that->normal.x, 0);

	float projectedDist = dot(diff, axisX);

	if (projectedDist > 0) axisX = -axisX;

	return dot(this->vel, axisX) >= 0 && //Check 1: Travelling towards the wall ?

		that->scale.x * 0.5 + this->scale.x > -dot(diff, axisX) && //Check 2: Radius + Thickness vs Distance

		that->scale.y * 0.5 > fabs(dot(diff, axisY)); //Check 3: Length check
}

void GameObject::WallCollisionResponse(GameObject* that)
{
	this->vel = this->vel - (2.0f * dot(this->vel, that->normal)) * that->normal;
}

bool GameObject::CheckCSCollision(GameObject* that)
{
	float distX = fabs(this->pos.x - that->pos.x);
	float distY = fabs(this->pos.y - that->pos.y);
	float distZ = fabs(this->pos.z - that->pos.z);
	return !((distX > this->scale.x / 2 + that->scale.x) || (distY > this->scale.y / 2 + that->scale.y) || (distZ > this->scale.z / 2 + that->scale.z));

}

bool GameObject::CheckCCCollision(GameObject* that)
{
	float distX = fabs(this->pos.x - that->pos.x);
	float distY = fabs(this->pos.y - that->pos.y);
	float distZ = fabs(this->pos.z - that->pos.z);
	return (distX < this->scale.x * 0.5f + that->scale.x * 0.5f) && (distY < this->scale.y * 0.5f + that->scale.y * 0.5f) && (distZ < this->scale.z * 0.5f + that->scale.z * 0.5f);
}

void GameObject::fixedUpdate(double dt)
{
	// check if button press
	slowdown = (glm::all(glm::equal(force, glm::vec3(0))));

	// check if the player is not pressing any button and the object is still moving
	if (slowdown && this->vel != glm::vec3(0)) {
		// add in resistance force to slowly, to simplify the whole equation, you could use -(obj->vel.x)
		// since mass is 1
		/*if (this->vel.x > 0) {
			force.x = -x_resistant;
		}
		else
			force.x = x_resistant;
		if (this->vel.y > 0) {
			force.y = -x_resistant;
		}
		else
			force.y = x_resistant;
		if (this->vel.z > 0) {
			force.z = -x_resistant;
		}
		else

			force.z = x_resistant;*/

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
	this->pos += 0.5f * static_cast<float>(dt) * (this->vel);

	float angularAcceleration = torque.z / this->momentOfInertia;
	this->anglularVelocity += angularAcceleration * dt;
	this->anglularVelocity = Math::Clamp(this->anglularVelocity, -ROTATION_SPEED, ROTATION_SPEED);

	//this->dir = RotateVector(this->dir, this->anglularVelocity * dt);
	// need all the forces to reset
	force = glm::vec3(0);
	torque = glm::vec3(0);
}

bool GameObject::CheckSSCollision(GameObject* that)
{
	// code the collision check here	
	return (glm::distance(this->pos, that->pos) < this->scale.x + that->scale.x);
}

void GameObject::CollisionResponse(GameObject* that)
{
	// code the collision response here
	glm::vec3 tempgo1 = this->vel;
	glm::vec3 tempthat = that->vel;

	float m1 = this->mass;
	float m2 = that->mass;

	glm::vec3 mom2 = m2 * tempthat;
	glm::vec3 mom1 = m1 * tempgo1;

	this->vel = glm::vec3(mom2.x / m1, mom2.y / m1, mom2.z / m1);
	that->vel = glm::vec3(mom1.x / m2, mom1.y / m2, mom1.z / m2);

	// step 1
	//glm::vec3 normal = glm::vec3(that->pos.x - this->pos.x, that->pos.y - this->pos.y, 0);
	glm::vec3 normal = that->pos - this->pos;
	normal = glm::normalize(normal);
	//std::cout << normal << std::endl;
	//float normalMagnitude = sqrtf((normal.x * normal.x) + (normal.y * normal.y));
	//glm::vec3 unitNormal = normal * (1 / normalMagnitude);
	glm::vec3 unitTangent;
	unitTangent.x = (-1 * normal.y);
	unitTangent.y = (normal.x);
	unitTangent.z = normal.z;
	float normalVel1, normalVel2, tangentVel1, tangentVel2;
	// step 3
	normalVel1 = dot(normal, this->vel);
	normalVel2 = dot(normal, that->vel);
	tangentVel1 = dot(unitTangent, this->vel);
	tangentVel2 = dot(unitTangent, that->vel);

	// step 5
	float vNormalVel1, vNormalVel2;
	vNormalVel1 = ((normalVel1 * (this->mass - that->mass)) + (2 * (that->mass * normalVel2))) * 1 / (this->mass + that->mass);
	vNormalVel2 = ((normalVel2 * (that->mass - this->mass)) + (2 * (this->mass * normalVel1))) * 1 / (this->mass + that->mass);

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
	that->vel = vPrimeNormalVel2 + vPrimeTanVel2;

	// Calculate the restitution coefficient (bounciness) of the collision
	float restitution = 0.5f;
	glm::vec3 relativeVelocity = that->vel - this->vel;
	float velocityAlongNormal = glm::dot(relativeVelocity, normal);
	// Calculate the impulse magnitude
	float impulseMagnitude = -(1 + restitution) * velocityAlongNormal /
		(1 / this->mass + 1 / that->mass);


	// Apply the impulse to the objects
	glm::vec3 impulse = impulseMagnitude * normal;
	this->vel -= impulse / this->mass;
	that->vel += impulse / that->mass;

	this->force = -normal;
	that->force = normal;


	//// Apply the impulse to the objects
	//glm::vec3 impulse = impulseMagnitude * normal;
	//this->vel -= impulse / this->mass;
	//that->vel += impulse / that->mass;

}
