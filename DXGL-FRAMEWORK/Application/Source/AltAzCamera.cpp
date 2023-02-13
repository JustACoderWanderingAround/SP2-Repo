#include "AltAzCamera.h"
//Include GLFW
#include <GLFW/glfw3.h>
#include "KeyboardController.h"
AltAzCamera::AltAzCamera() : phi(0.0f), theta(0.0f), dist(0.0f), isDirty(false)
{
}
AltAzCamera::~AltAzCamera()
{
}
int AltAzCamera::getDist()
{
	return dist;
}
void AltAzCamera::Init(float theta, float phi, float dist)
{
	this->theta = theta;
	this->phi = phi;
	this->dist = dist;
	this->isDirty = true;
	Refresh();
}

void AltAzCamera::Update(double dt)
{
	static const float ROTATE_SPEED = 100.0f;
	static const float ZOOM_SPEED = 10.0f;
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT)) {
		theta -= ROTATE_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_RIGHT)) {
		theta += ROTATE_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_UP)) {
		phi += ROTATE_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_DOWN)) {
		phi -= ROTATE_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_W)) {
		dist -= ZOOM_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_S)) {
		dist += ZOOM_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_PAGE_DOWN)) {
		target.y -= ZOOM_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_PAGE_UP)) {
		target.y += ZOOM_SPEED * static_cast<float>(dt);
		isDirty = true;
	}
	this->Refresh();
}

void AltAzCamera::Refresh()
{
	if (!isDirty) return;
	// Calculate the position based on dist
	float x = this->dist * cosf(glm::radians(this->phi)) * cosf(glm::radians(this->theta));
	float y = this->dist * sinf(glm::radians(this->phi));
	float z = this->dist * cosf(glm::radians(this->phi)) * sinf(glm::radians(this->theta));
	this->position = glm::vec3(x, y, z);
	// Set default target to origin for this camera
	this->target = glm::vec3(target.x, target.y, target.z);
	glm::vec3 view = glm::normalize(target - position);
	// Find the right vector using default up (0,1,0) first
	glm::vec3 right = glm::normalize(glm::cross(view, glm::vec3(0.f, 1.f, 0.f)));
	// Recalculate the up vector
	this->up = glm::normalize(glm::cross(right, view));
	isDirty = false;
}
