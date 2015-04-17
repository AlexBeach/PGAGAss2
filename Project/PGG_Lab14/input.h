#pragma once

#include <glm.hpp>
#include <SDL.h>
#include "glew.h"
#include <iostream>
#include "wglew.h"

class input
{
public:
	input(void);
	~input(void);

	void GameInputs(SDL_Event Event);

	bool getQuit(void);
	bool getUp(void);
	bool getDown(void);
	bool getLeft(void);
	bool getRight(void);
	bool getPower(void);

private:

	bool Quit, Up, Down, Left, Right, Power;
};