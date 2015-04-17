//#pragma once
//
//#include <glm.hpp>
//#include <SDL.h>
//#include <vector>
//#include <string>
//#include "glew.h"
//#include "Shader.h"
//#include "ObjectLoader.h"
//#include "wglew.h"
//
//class PoolCue
//{
//public:
//	PoolCue(std::string filename/*, glm::vec3 Pos*/);
//	~PoolCue(void);
//
//	/// Currently just updates rotation to make the model rotate
//	void Update(float deltaTs);
//
//	/// Draws object using the given camera view and projection matrices
//	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);
//
//private:
//
//	// Create a model
//	ObjectLoader *Object;
//
//	/// Object position vector
//	glm::vec3 position;
//
//	/// Euler angles for rotation
//	glm::vec3 rotation;
//
//	/// Object's model matrix
//	/// This is rebuilt in the update function
//	glm::mat4 modelMatrix;
//};