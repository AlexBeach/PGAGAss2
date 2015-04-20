#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <iostream>
#include <string>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "glew.h"
#include "Shader.h"
#include "Input.h"
#include "ObjectLoader.h"

class GameEntity
{
public:
	inline GameEntity(void) {}
	inline ~GameEntity(void) {}

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	void setPos(glm::vec3 Pos) { Pos = position; };
	glm::vec3 GetPosition() { return position; };

	void AttachMesh(ObjectLoader* mesh);

protected:
	
	void UpdateMatrix();

	/// Object position vector
	glm::vec3 position;

	/// Euler angles for rotation
	glm::vec3 rotation;

	//scale
	glm::vec3 scale;

	/// Object's model matrix
	/// This is rebuilt in the update function
	glm::mat4 modelMatrix;

private:

	// Create a model
	ObjectLoader *Object;
};