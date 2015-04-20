#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <string>
#include "glew.h"
#include "Shader.h"
#include "ObjectLoader.h"
#include "wglew.h"

class GameEntity
{
public:
	inline GameEntity(void) {}
	inline ~GameEntity(void) {}

	/// Currently just updates rotation to make the model rotate
	void Update(float deltaTs);

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	void setPos(glm::vec3 Pos);
	glm::vec3 getPos(void);

	void AttachMesh(ObjectLoader* mesh);

	void UpdateMatrix(glm::vec3 pos, glm::vec3 rot, float scale);

protected:
	/// Object position vector
	glm::vec3 position;

	/// Euler angles for rotation
	glm::vec3 rotation;

	//scale
	float scale;

	/// Object's model matrix
	/// This is rebuilt in the update function
	glm::mat4 modelMatrix;

	// Create a model
	ObjectLoader *Object;
};