#pragma once

#include <glm.hpp>
#include <SDL.h>
#include "glew.h"
#include "wglew.h"

class Shader
{
public:
	Shader(void);
	~Shader(void);

	/// Loads shaders for the object into OpenGL
	void InitialiseShaders();

	inline	GLuint Program() { return program; }
	inline GLint ModelMat() { return ModelMatLocation; }
	inline GLint ViewMat() { return ViewMatLocation; }
	inline GLint ProjMat() { return ProjMatLocation; }

private:

	/// Shader program
	GLuint program;

	/// Uniform locations
	GLint ModelMatLocation, ViewMatLocation, ProjMatLocation;
};

