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

	void GameInputs(void);

	bool isQuitDown(void);
	bool isUpDown(void);
	bool isDownDown(void);
	bool isLeftDown(void);
	bool isRightDown(void);
	bool isFireDown(void);

private:

	// Here we are going to check for any input events
	// Basically when you press the keyboard or move the mouse, the parameters are stored as something called an 'event'
	// SDL has a queue of events
	// We need to check for each event and then do something about it (called 'event handling')
	// the SDL_Event is the datatype for the event
	SDL_Event incomingEvent;

	bool Quit, Up, Down, Left, Right, Fire;
};