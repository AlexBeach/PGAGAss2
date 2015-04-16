#include "input.h"

input::input(void)
{
	Quit = Up = Down = Left = Right = Power = false;
}

input::~input(void)
{

}

void input::GameInputs(SDL_Event Event)
{
	// SDL_PollEvent will check if there is an event in the queue
	// If there's nothing in the queue it won't sit and wait around for an event to come along (there are functions which do this, and that can be useful too!)
	// For an empty queue it will simply return 'false'
	// If there is an event, the function will return 'true' and it will fill the 'incomingEvent' we have given it as a parameter with the event data
	while(SDL_PollEvent(&Event))
	{
		// If we get in here, we have an event and need to figure out what to do with it
		// For now, we will just use a switch based on the event's type
		switch(Event.type)
		{
			case SDL_QUIT:
				// The event type is SDL_QUIT
				// This means we have been asked to quit - probably the user clicked on the 'x' at the top right corner of the window
				// To quit we need to set our 'go' bool to false so that we can escape out of the game loop
				Quit = true;
				break;

				// If you want to learn more about event handling and different SDL event types, see:
				// https://wiki.libsdl.org/SDL_Event
				// and also: https://wiki.libsdl.org/SDL_EventType
				// but don't worry, we'll be looking at handling user keyboard and mouse input soon

			case SDL_KEYDOWN:
				// The event type is SDL_KEYDOWN
				// This means that the user has pressed a key
				// Let's figure out which key they pressed
				switch(Event.key.keysym.sym)
				{
					case SDLK_UP:
					case SDLK_w:	Up = true;
						break;
					case SDLK_DOWN:
					case SDLK_s:	Down = true;
						break;
					case SDLK_LEFT:
					case SDLK_a:	Left = true;
						break;
					case SDLK_RIGHT:
					case SDLK_d:	Right = true;
						break;
				}
				break;

			case SDL_KEYUP:
				// The event type is SDL_KEYUP
				// This means that the user has released a key
				// Let's figure out which key they pressed
				switch(Event.key.keysym.sym)
				{
					case SDLK_UP:
					case SDLK_w:	Up = false;
						break;
					case SDLK_DOWN:
					case SDLK_s:	Down = false;
						break;
					case SDLK_LEFT:
					case SDLK_a:	Left = false;
						break;
					case SDLK_RIGHT:
					case SDLK_d:	Right = false;
						break;
				}
				break;
		}
	}
}

bool input::getQuit()
{
	return Quit;
}

bool input::getUp(void)
{
	return Up;
}

bool input::getDown(void)
{
	return Down;
}

bool input::getLeft(void)
{
	return Left;
}

bool input::getRight(void)
{
	return Right;
}

bool input::getPower(void)
{
	return Power;
}