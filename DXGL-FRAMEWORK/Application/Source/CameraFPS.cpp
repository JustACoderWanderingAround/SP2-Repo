#include "CameraFPS.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include "GLFW/glfw3.h"

CameraFPS::CameraFPS()
{
}

CameraFPS::~CameraFPS()
{
}

void CameraFPS::Init(const glm::vec3& pos, const glm::vec3& target, const glm::vec3& up, bool mouseControl, bool keyBoardControl)
{
	Camera::Init(pos, target, up);
	this->mouseControl = mouseControl;
	this->fieldOfView = fieldOfView;
	this->keyBoardControl = keyBoardControl;
}

void CameraFPS::Reset()
{
}

void CameraFPS::Update(double dt)
{
	static const float ROTATE_SPEED = 50.0f;
	static float ZOOM_SPEED = 2.0f;

	glm::vec3 view = glm::normalize(target - position); // calculate the new view vector
	glm::vec3 right = glm::normalize(glm::cross(view, up));


	//roh tah teh
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT)) {
		//Calculate amount of angle to rotate
		float angle = ROTATE_SPEED * static_cast<float>(dt);
		glm::mat4 yaw = glm::rotate(
			glm::mat4(1.f), // Default identity
			glm::radians(angle), // Convert degree angle to radians
			glm::vec3(up.x, up.y, up.z) // Use camera Up vector to rotate
		);
		// Calculate the rotated view vector
		rotatedView = yaw * glm::vec4(view, 0.f);
		target = position + rotatedView;
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_RIGHT)) {
		// Implement the camera rotations
		//Calculate amount of angle to rotate
		float angle = -1 * ROTATE_SPEED * static_cast<float>(dt);
		glm::mat4 yaw = glm::rotate(
			glm::mat4(1.f), // Default identity
			glm::radians(angle), // Convert degree angle to radians
			glm::vec3(up.x, up.y, up.z) // Use camera Up vector to rotate
		);
		// Calculate the rotated view vector
		rotatedView = yaw * glm::vec4(view, 0.f);
		target = position + rotatedView;
		isDirty = true;
	}
	if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_UP)) {
		right.y = 0; // Right vector should not point any y direction
		float angle = 1 * ROTATE_SPEED * static_cast<float>(dt);
		glm::mat4 pitch = glm::rotate(
			glm::mat4(1.f),
			glm::radians(angle),
			glm::vec3(right.x, right.y, right.z)
		); // Rotate on right vector
		rotatedView = pitch * glm::vec4(view, 0);
		target = position + rotatedView;
		isDirty = true;
	}
	else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_DOWN)) {
		right.y = 0; // Right vector should not point any y direction
		float angle = -1 * ROTATE_SPEED * static_cast<float>(dt);
		glm::mat4 pitch = glm::rotate(
			glm::mat4(1.f),
			glm::radians(angle),
			glm::vec3(right.x, right.y, right.z)
		); // Rotate on right vector
		rotatedView = pitch * glm::vec4(view, 0);
		target = position + rotatedView;
		isDirty = true;
	}
	// nyoom
	if (keyBoardControl) {
		if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_W)) {
			if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
				ZOOM_SPEED = 5.0f;
			}
			position += view * glm::vec3(ZOOM_SPEED, 0, ZOOM_SPEED) * glm::vec3(static_cast<float>(dt), 0, static_cast<float>(dt));
			target += view * glm::vec3(ZOOM_SPEED, 0, ZOOM_SPEED) * glm::vec3(static_cast<float>(dt), 0, static_cast<float>(dt));
			isDirty = true;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_S)) {
			if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
				ZOOM_SPEED = 5.0f;
			}
			// To do for opposite direction
			position -= view * glm::vec3(ZOOM_SPEED, 0, ZOOM_SPEED) * glm::vec3(static_cast<float>(dt), 0, static_cast<float>(dt));
			target -= view * glm::vec3(ZOOM_SPEED, 0, ZOOM_SPEED) * glm::vec3(static_cast<float>(dt), 0, static_cast<float>(dt));
			isDirty = true;
		}
		if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_D)) {
			if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
				ZOOM_SPEED = 5.0f;
			}
			position += right * ZOOM_SPEED * static_cast<float>(dt); // Use right vector
			target += right * ZOOM_SPEED * static_cast<float>(dt); // Use right vector
			isDirty = true;
		}
		else if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_A)) {
			if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
				ZOOM_SPEED = 5.0f;
			}
			// To do: for opposite direction
			position -= right * ZOOM_SPEED * static_cast<float>(dt); // Use right vector
			target -= right * ZOOM_SPEED * static_cast<float>(dt); // Use right vector
			isDirty = true;
		}
		if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_Q)) {
			position.y -= ZOOM_SPEED * static_cast<float>(dt);
			target.y -= ZOOM_SPEED * static_cast<float>(dt);
			isDirty = true;
		}
		if (KeyboardController::GetInstance()->IsKeyDown(GLFW_KEY_E)) {
			position.y += ZOOM_SPEED * static_cast<float>(dt);
			target.y += ZOOM_SPEED * static_cast<float>(dt);
			isDirty = true;
		}
	}
		//TODO: UNCOMMENT WHEN DONE MODELLING SCENE
	if (mouseControl) {
		double deltaX = MouseController::GetInstance()->GetMouseDeltaX();
		double deltaY = MouseController::GetInstance()->GetMouseDeltaY();

		float angleX = -deltaX * ROTATE_SPEED * 0.3f * static_cast<float>(dt);
		float angleY = -deltaY * ROTATE_SPEED * 0.3f * static_cast<float>(dt);
		glm::mat4 yaw = glm::rotate(
			glm::mat4(1.f),// matrix to modify
			glm::radians(angleX),// rotation angle in degree and converted to radians
			glm::vec3(up.x, up.y, up.z)// the axis to rotate along
		);

		glm::mat4 pitch = glm::rotate(
			glm::mat4(1.f),
			glm::radians(angleY),
			glm::vec3(right.x, right.y, right.z)
		); // Rotate on right vector
		yawView = yaw * glm::vec4(view, 0.f);
		glm::vec3 pitchView = pitch * glm::vec4(view, 0.f);
		target = position + (pitchView + yawView);
	}
	
	isDirty = true;

	//this->Refresh();

}


void CameraFPS::Refresh()
{
	Camera::Refresh();
}

