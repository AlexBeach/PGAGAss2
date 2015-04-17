#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <string>
#include "glew.h"
#include "Shader.h"
#include "ObjectLoader.h"

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations

class GameEntity
{
public:
	GameEntity(void);
	~GameEntity(void);

	/// Currently just updates rotation to make the model rotate
	void Update(glm::vec3 pos, glm::vec3 rot, float deltaTs);

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

private:

	// Create a model
	ObjectLoader *Object;
};