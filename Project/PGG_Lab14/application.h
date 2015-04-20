#pragma once

#include <glm.hpp>
#include <SDL.h>
#include "glew.h"
#include <iostream>
#include "input.h"
#include "wglew.h"
#include "Sphere.h"
#include "Cube.h"

class application
{
public:
	application(void);
	~application(void);

	void Init();
	void InitEntities(void);
	bool Update(int dt);
	void Draw(void);

private:

	int winPosX, winPosY, winWidth, winHeight;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_GLContext glcontext;

	// call the input class to contrust object for managing game input in this game
	input *GameInput;

	//call the game entity class to create pool ball
	Sphere *Sphere1;

	std::vector<Cube*> CubeArray;
	Cube *Cube1;

	int NumOfCubes;

	// Here we are going to check for any input events
	// Basically when you press the keyboard or move the mouse, the parameters are stored as something called an 'event'
	// SDL has a queue of events
	// We need to check for each event and then do something about it (called 'event handling')
	// the SDL_Event is the datatype for the event
	SDL_Event incomingEvent;
};