#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "KeyboardController.h"

class AltAzCamera
{
	float phi;
	float theta;
	float dist;
	
	bool isDirty; // checks if need to recalc cam attribute

	void Refresh();
public:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;

	AltAzCamera();
	~AltAzCamera();
	int getDist();
	void Init(float theta, float phi, float dist);
	void Reset();
	void Update(double dt);

};

