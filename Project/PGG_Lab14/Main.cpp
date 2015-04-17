#include <SDL.h>
#include "glew.h"
#include <iostream>
#include "application.h"

// The GLM library contains vector and matrix functions and classes for us to use
// They are designed to easily work with OpenGL
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations

// An initialisation function, mainly for GLEW
// This will also print to console the version of OpenGL we are using
bool InitGL()
{
	// GLEW has a problem with loading core OpenGL
	// See here: https://www.opengl.org/wiki/OpenGL_Loading_Library
	// The temporary workaround is to enable its 'experimental' features
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr<<"Error: GLEW failed to initialise with message: "<< glewGetErrorString(err) <<std::endl;
		//return false;
	}
	std::cout<<"INFO: Using GLEW "<< glewGetString(GLEW_VERSION)<<std::endl;

	std::cout<<"INFO: OpenGL Vendor: "<< glGetString( GL_VENDOR ) << std::endl;
	std::cout<<"INFO: OpenGL Renderer: "<< glGetString( GL_RENDERER ) << std::endl;
	std::cout<<"INFO: OpenGL Version: "<< glGetString( GL_VERSION ) << std::endl;
	std::cout<<"INFO: OpenGL Shading Language Version: "<< glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

	return true;
}

int main(int argc, char *argv[])
{
	// We are going to work out how much time passes from frame to frame
	// We will use this variable to store the time at our previous frame
	// This function returns the number of milliseconds since SDL was initialised
	unsigned int lastTime = SDL_GetTicks();

	// SDL_Init is the main initialisation function for SDL
	// It takes a 'flag' parameter which we use to tell SDL what systems we're going to use
	// Here, we want to use SDL's video system, so we give it the flag for this
	// Incidentally, this also initialises the input event system
	// This function also returns an error value if something goes wrong
	// So we can put this straight in an 'if' statement to check and exit if need be
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		// Something went very wrong in initialisation, all we can do is exit
		std::cout<<"Whoops! Something went very wrong, cannot initialise SDL :("<<std::endl;
		return -1;
	}

	application *App = new application();

	// Call our initialisation function to set up GLEW and print out some GL info to console
	if(!InitGL())
	{
		return -1;
	}

	App->Init();
	App->InitEntities();

	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it)
	//   * Update our world
	//   * Draw our world
	bool Go = true;
	while(Go)
	{
		// We are going to work out the time between each frame now
		// First, find the current time
		// again, SDL_GetTicks() returns the time in milliseconds since SDL was initialised
		// We can use this as the current time
		unsigned int current = SDL_GetTicks();
		// Next, we want to work out the change in time between the previous frame and the current one
		// This is a 'delta' (used in physics to denote a change in something)
		// So we call it our 'deltaT' and I like to use an 's' to remind me that it's in seconds!
		// (To get it in seconds we need to divide by 1000 to convert from milliseconds)
		float deltaTs = (float) (current - lastTime) / 1000.0f;
		// Now that we've done this we can use the current time as the next frame's previous time
		lastTime = current;

		// Update our world
		Go = App->Update(deltaTs);
		
		// Draw our world
		App->Draw();
		
		// Limiter in case we're running really quick
		if( deltaTs < (1.0f/50.0f) )	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int) (((1.0f/50.0f) - deltaTs)*1000.0f) );
		}
	}
	// If we get outside the main game loop, it means our user has requested we exit

	return 0;
}