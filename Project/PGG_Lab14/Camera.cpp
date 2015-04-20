#include "Camera.h"

Camera::Camera(void)
{
		// Construct a projection matrix for the camera
		projectionMatrix = glm::perspective(70.0f, 16.0f / 9.0f, 0.1f, 600.0f);

		// Create a viewing matrix for the camera
		// Don't forget, this is the opposite of where the camera actually is
		// You can think of this as moving the world away from the camera
		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-2.5f) );

		speed = 1.0f;

		fov = 45;
		steve = 0;
		position = glm::vec3(0,0,0);
}

Camera::~Camera(void)
{
}

void Camera::update(glm::vec3 targetPosition, float movement)
{
	steve += movement / 77.7f;
	float newfov = 70 + sin(steve) * 2.7f;


	glm::vec3 newPos;
	newPos.x = position.x + (targetPosition.x / movement);
	newPos.y = position.y + (targetPosition.y / movement);
	viewMatrix = glm::lookAt(newPos, newPos + glm::vec3(0, 0, -1),glm::vec3(0, 1, 0));
	//projectionMatrix = glm::perspective(newfov, 16.0f / 9.0f, 0.1f, 200.0f);				//UNCOMMENT FOR AWESOMENESS
}