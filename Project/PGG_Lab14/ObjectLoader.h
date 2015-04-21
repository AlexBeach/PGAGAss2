//#ifndef _OBJECTLOADER_H_
//#define _OBJECTLOADER_H_
//
//#include <glm.hpp>
//#include <SDL.h>
//#include <vector>
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <gtc/type_ptr.hpp>
//#include <gtc/matrix_transform.hpp>
//#include "glew.h"
//#include "Shader.h"
//
//class ObjectLoader
//{
//public:
//	ObjectLoader(std::string filename);
//	~ObjectLoader(void);
//
//	/// Currently just updates rotation to make the model rotate
//	void Update(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
//
//	/// Draws object using the given camera view and projection matrices
//	void Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix);
//
//	void setMat(glm::mat4 modMatrix);
//
//protected:
//
//	/// loads the object from an obj file
//	void LoadObject(std::string filename);
//
//	/// create vao
//	void CreateVAO();
//	
//	/// Vertex Array Object for model in OpenGL
//	GLuint VAO;
//
//	/// Object's model matrix
//	/// This is rebuilt in the update function
//	glm::mat4 modelMatrix;
//
//	/// Number of vertices in the model
//	unsigned int numVertices;
//
//	std::vector<glm::vec3> vertices, normals;
//	std::vector<glm::vec2> UVs;
//
//	Shader *shader;
//};
//#endif