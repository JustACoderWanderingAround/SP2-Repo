#include "Camera.h"




Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

void Camera::Reset()
{
}

void Camera::Update(double dt)
{
}

void Camera::Refresh()
{
	
	if (!this->isDirty) return;

	glm::vec3 view = glm::normalize(target - position);
	glm::vec3 right = glm::normalize(glm::cross(view, up));

	// Recalculate the up vector
	this->up = glm::normalize(glm::cross(right, view));

	this->isDirty = false;
	

}
