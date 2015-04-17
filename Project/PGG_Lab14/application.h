#pragma once

#include <SDL.h>
#include "glew.h"
#include <iostream>
#include "GameEntity.h"
#include "input.h"

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL!
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations

class application
{
public:
	application(void);
	~application(void);

	//bool InitGL(void);
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

	//call the game entity class to create a game entity, in this case a pool ball
	GameEntity *PoolBall1;

	// Here we are going to check for any input events
	// Basically when you press the keyboard or move the mouse, the parameters are stored as something called an 'event'
	// SDL has a queue of events
	// We need to check for each event and then do something about it (called 'event handling')
	// the SDL_Event is the datatype for the event
	SDL_Event incomingEvent;
};