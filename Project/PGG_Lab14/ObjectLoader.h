#ifndef _OBJECTLOADER_H_
#define _OBJECTLOADER_H_

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <string>
#include "glew.h"
#include "Shader.h"
#include "wglew.h"

class ObjectLoader
{
public:
	ObjectLoader(std::string filename);
	~ObjectLoader(void);

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	void setMat(glm::mat4 modMatrix);

protected:

	/// loads the object from an obj file
	void LoadObject(std::string filename);

	/// create vao
	void CreateVAO();
	
	/// Object position vector
	glm::vec3 position;

	/// Euler angles for rotation
	glm::vec3 rotation;

	/// Vertex Array Object for model in OpenGL
	GLuint VAO;

	/// Object's model matrix
	/// This is rebuilt in the update function
	glm::mat4 modelMatrix;

	/// Number of vertices in the model
	unsigned int numVertices;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	Shader *shader;
};
#endif