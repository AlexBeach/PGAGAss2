#pragma once

#include <glm.hpp>
#include <SDL.h>
#include <vector>
#include <string>
#include "glew.h"
#include "Shader.h"
#include "ObjectLoader.h"
#include "wglew.h"
#include "gameentity.h"

class Cube: public GameEntity
{
public:
	Cube(void);
	~Cube(void);

	/// Currently just updates rotation to make the model rotate
	void Update(float deltaTs);
};
