#ifndef __MESH_H_
#define __MESH_H_

 
 //Mesh.h
 //SDL Assignment 2
 //This class contains data to handle mesh data from a loaded obj file
 

#include <glm.hpp>
#include <SDL.h>
#include <string>
#include "glew.h"
#include "ObjLoader.h"

// Class to store and display a model
class Mesh
{
public:

	// Constructor calls InitialiseVAO and InitialiseShaders
	Mesh(std::string objFileName);
	~Mesh();
	
	// Load in a texture
	void LoadTexture(const char* filename);

	// Loads object model into OpenGL
	void InitialiseVAO();

	// Loads shaders for the object into OpenGL
	void InitialiseShaders();

	// Currently just updates rotation to make the model rotate
	void Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

	// Draws object using the given camera view and projection matrices
	void Draw(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 light);

	void BoundingBoxCoords(void);

	inline glm::vec3 getMin(void) { return Min; };
	inline glm::vec3 getMax(void) { return Max; };
	glm::vec3 getDistance(void);
	glm::mat4 getModelMatrix(void) { return modelMatrix; };
	
protected:
	// process an obj file
	ObjLoader objLoader;

	// Vertex Array Object for model in OpenGL
	GLuint VAO;

	// Shader program
	GLuint shader;
	
	// Get a handle for our "MVP" uniform
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;

	// Object's model matrix
	// This is rebuilt in the update function
	glm::mat4 modelMatrix;
	
	// opengl index for the loaded textures
	GLuint diffuseTexID;
	GLuint normalTexID;

private:

	// private buffers for the loaded model data
	GLuint positionBuffer;
	GLuint normalBuffer;
	GLuint texCoordBuffer;
	GLuint tangentBuffer;
	GLuint biTangentBuffer;

	std::string ReadFile(std::string fileName);

	glm::vec3 Min, Max;

	unsigned int numVertices;
};
#endif
