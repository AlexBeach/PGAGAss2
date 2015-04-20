#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#pragma once
class Camera
{
public:
	Camera(void);
	~Camera(void);

	inline glm::mat4 getViewMatrix() {return viewMatrix; };
	inline glm::mat4 getprojectionMatrix() {return projectionMatrix; };

	void update (glm::vec3 position, float movement);

private:

	glm::vec3 position;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	float speed;
	float pitch, yaw;
	float fov;
	float steve;
};

