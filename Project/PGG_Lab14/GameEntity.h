#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <iostream>
#include <string>
#include <time.h>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "glew.h"
#include "Mesh.h"
#include "Input.h"

class GameEntity
{
public:
	inline GameEntity(void) {}
	inline ~GameEntity(void) {}

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, glm::vec3 light);

	bool Collision(glm::vec3 MinPos, glm::vec3 MaxPos, glm::vec3 Pos, glm::vec3 OtherMinPos, glm::vec3 OtherMaxPos, glm::vec3 OtherPos);

	void AttachMesh(Mesh* mesh);

	inline void setPos(glm::vec3 Pos) { Pos = position; };
	inline glm::vec3 GetPosition() { return position; };

	glm::vec3 getMin(void) { return Object->getMin(); };
	glm::vec3 getMax(void) { return Object->getMax(); };
	inline glm::vec3 getDist(void) { return Object->getDistance(); };

protected:
	
	void UpdateMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 s);

	/// Object position vector
	glm::vec3 position;

	/// Euler angles for rotation
	glm::vec3 rotation;

	glm::vec3 SMin, SMax;

	//scale
	glm::vec3 scale;
	float scaler;

	///// Object's model matrix
	///// This is rebuilt in the update function
	//glm::mat4 modelMatrix;

	float Speed;

private:

	// Create a model
	Mesh *Object;
};