
#include "GameObject.h"
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

static Vector3 RotateVector(const Vector3& vec, float radian)
{
	return Vector3(vec.x * cos(radian) + vec.y * -sin(radian),
		vec.x * sin(radian) + vec.y * cos(radian), 0.f);
}

bool GameObject::CheckLineCollision(GameObject* go1, GameObject* go2)
{
	Vector3 diff = go1->pos - go2->pos;
	Vector3 axisX = go2->normal;
	Vector3 axisY = Vector3(-go2->normal.y, go2->normal.x, 0);

	float projectedDist = diff.Dot(axisX);

	if (projectedDist > 0) axisX = -axisX;

	return go1->vel.Dot(axisX) >= 0 && //Check 1: Travelling towards the wall ?
		go2->scale.x * 0.5 + go1->scale.x > -diff.Dot(axisX) && //Check 2: Radius + Thickness vs Distance
		go2->scale.y * 0.5 > fabs(diff.Dot(axisY)); //Check 3: Length check
}

void GameObject::WallCollisionResponse(GameObject* go1, GameObject* go2)
{
	go1->vel = go1->vel - (2.0f * go1->vel.Dot(go2->normal)) * go2->normal;
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
	slowdown = force.IsZero();

	// check if the player is not pressing any button and the object is still moving
	if (slowdown && !this->vel.IsZero()) {
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
	Vector3 acc;
	acc = force * multiplier;

	Vector3 temp;
	// set initial velocity (U)
	temp = this->vel;

	//commpute the resulting velocity.
	// v = u + at
	this->vel += (float)dt * timeScale * acc;

	// need to check if it's meant to stop the object or not
	// aka check if the player is pressing
	if (slowdown &&
		(this->vel.x > 0 && temp.x < 0) || (this->vel.x < 0 && temp.x > 0))
		this->vel.SetZero();
	// s = 1/2 (u+v)t
	this->pos += 0.5f * (float)dt * timeScale * (temp + this->vel);

	float angularAcceleration = torque.z / this->momentOfInertia;
	this->anglularVelocity += angularAcceleration * dt;
	this->anglularVelocity = Math::Clamp(this->anglularVelocity, -ROTATION_SPEED, ROTATION_SPEED);

	this->dir = RotateVector(this->dir, this->anglularVelocity * dt);
	// need all the forces to reset
	force.SetZero();
	torque.SetZero();
}

bool GameObject::CheckSSCollision(GameObject* A, GameObject* B)
{
	// code the collision check here	
	return (A->pos.Distance(B->pos) < A->scale.x + B->scale.x);
}

void GameObject::CollisionResponse(GameObject* go1, GameObject* go2)
{
	// code the collision response here
	Vector3 tempgo1 = go1->vel;
	Vector3 tempgo2 = go2->vel;

	float m1 = go1->mass;
	float m2 = go2->mass;

	Vector3 mom2 = m2 * tempgo2;
	Vector3 mom1 = m1 * tempgo1;

	go1->vel.Set(mom2.x / m1, mom2.y / m1, 0);
	go2->vel.Set(mom1.x / m2, mom1.y / m2, 0);

	// step 1
	//Vector3 normal = Vector3(go2->pos.x - go1->pos.x, go2->pos.y - go1->pos.y, 0);
	Vector3 normal = go2->pos - go1->pos;
	normal = normal.Normalize();
	//std::cout << normal << std::endl;
	//float normalMagnitude = sqrtf((normal.x * normal.x) + (normal.y * normal.y));
	//Vector3 unitNormal = normal * (1 / normalMagnitude);
	Vector3 unitTangent;
	unitTangent.x = (-1 * normal.y);
	unitTangent.y = (normal.x);
	float normalVel1, normalVel2, tangentVel1, tangentVel2;
	// step 3
	normalVel1 = normal.Dot(go1->vel);
	normalVel2 = normal.Dot(go2->vel);
	tangentVel1 = unitTangent.Dot(go1->vel);
	tangentVel2 = unitTangent.Dot(go2->vel);

	// step 5
	float vNormalVel1, vNormalVel2;
	vNormalVel1 = ((normalVel1 * (go1->mass - go2->mass)) + (2 * (go2->mass * normalVel2))) * 1 / (go1->mass + go2->mass);
	vNormalVel2 = ((normalVel2 * (go2->mass - go1->mass)) + (2 * (go1->mass * normalVel1))) * 1 / (go1->mass + go2->mass);

	// step 6
	Vector3 vPrimeNormalVel1, vPrimeNormalVel2, vPrimeTanVel1, vPrimeTanVel2;

	// v1prime
	vPrimeNormalVel1 = normal * vNormalVel1;
	vPrimeTanVel1 = unitTangent * tangentVel1;

	// v2prime
	vPrimeNormalVel2 = normal * vNormalVel2;
	vPrimeTanVel2 = unitTangent * tangentVel2;

	// step 7
	go1->vel = vPrimeNormalVel1 + vPrimeTanVel1;
	go2->vel = vPrimeNormalVel2 + vPrimeTanVel2;

}