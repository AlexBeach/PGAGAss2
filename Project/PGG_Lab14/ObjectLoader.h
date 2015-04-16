#ifndef _OBJECTLOADER_H_
#define _OBJECTLOADER_H_

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <string>
#include "glew.h"
#include "Shader.h"

class ObjectLoader
{
public:
	ObjectLoader(std::string filename);
	~ObjectLoader(void);

	/// Currently just updates rotation to make the model rotate
	void Update(glm::vec3 pos, glm::vec3 rot, float deltaTs);

	/// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);

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
	glm::mat4 _modelMatrix;

	/// Number of vertices in the model
	unsigned int numVertices;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	Shader *shader;
};
#endif