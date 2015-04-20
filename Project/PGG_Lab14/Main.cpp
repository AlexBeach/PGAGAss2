#include <SDL.h>
#include "glew.h"
#include <iostream>
#include <time.h>
#include <glm.hpp> // This is the main GLM header
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations
#include "input.h"
#include "Sphere.h"
#include "Cube.h"
#include "Camera.h"
//#include "Application.h"

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
		return false;
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

	// This is how we set the context profile
	// We need to do this through SDL, so that it can set up the OpenGL drawing context that matches this
	// (of course in reality we have no guarantee this will be available and should provide fallback methods if it's not!)
	// Anyway, we basically first say which version of OpenGL we want to use
	// So let's say 4.3:
	// Major version number (4):
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	// Minor version number (3):
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	// Then we say whether we want the core profile or the compatibility profile
	// Flag options are either: SDL_GL_CONTEXT_PROFILE_CORE   or   SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
	// We'll go for the core profile
	// This means we are using the latest version and cannot use the deprecated functions
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	
	 //Now we have got SDL initialised, we are ready to create a window!
	 //These are some variables to help show you what the parameters are for this function*
	 //You can experiment with the numbers to see what they do
	int winPosX = 100;
	int winPosY = 100;
	int winWidth = 1280;
	int winHeight = 720;
	
	SDL_Window *window = SDL_CreateWindow("Underwater Game",  // The first parameter is the window title
		winPosX, winPosY,
		winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	// The last parameter lets us specify a number of options
	// Here, we tell SDL that we want the window to be shown and that it can be resized
	// You can learn more about SDL_CreateWindow here: https://wiki.libsdl.org/SDL_CreateWindow?highlight=%28\bCategoryVideo\b%29|%28CategoryEnum%29|%28CategoryStruct%29
	// The flags you can pass in for the last parameter are listed here: https://wiki.libsdl.org/SDL_WindowFlags
	
	// The SDL_CreateWindow function returns an SDL_Window
	// This is a structure which contains all the data about our window (size, position, etc)
	// We will also need this when we want to draw things to the window
	// This is therefore quite important we don't lose it!
	
	// The SDL_Renderer is a structure that handles rendering
	// It will store all of SDL's internal rendering related settings
	// When we create it we tell it which SDL_Window we want it to render to
	// That renderer can only be used for this window
	// (yes, we can have multiple windows - feel free to have a play sometime)
	SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, 0 );
	
	// Now that the SDL renderer is created for the window, we can create an OpenGL context for it!
	// This will allow us to actually use OpenGL to draw to the window
	SDL_GLContext glcontext = SDL_GL_CreateContext( window );
	
	// Call our initialisation function to set up GLEW and print out some GL info to console
	if(!InitGL()) { return -1; }
	
	// We are going to work out how much time passes from frame to frame
	// We will use this variable to store the time at our previous frame
	// This function returns the number of milliseconds since SDL was initialised
	unsigned int lastTime = SDL_GetTicks();
		
	// Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
	glEnable(GL_DEPTH_TEST);

	//application *App = new application();

	//App->Run();

	srand(time(NULL));
	
	std::vector<Cube*> CubeArray;
	
	int NumOfCubes = 1000;
	
	ObjectLoader* CubeMesh = new ObjectLoader("Cube.obj");
	ObjectLoader* playerMesh = new ObjectLoader("Sphere.obj");
	
	// Create a model
	Sphere *myPlayer = new Sphere();
	myPlayer->AttachMesh(playerMesh);
	
	Camera* camera = new Camera();
	
	for(int i = 0; i < NumOfCubes; i++)
	{
		float x, y, z;
	
		x = rand() % 80 - 40; //random number between 0 and *number* minus *number*
		y = rand() % 40 - 30;
		z = -300 - (i * (20 - (rand() % 40)) / 20);
	
		Cube* cube = new Cube();
		cube->AttachMesh(CubeMesh);
		cube->SetPosition(glm::vec3(x, y, z));
	
		CubeArray.push_back(cube);
	}

	// We are now preparing for our main loop (also known as the 'game loop')
	// This loop will keep going round until we exit from our program by changing the bool 'go' to the value false
	// This loop is an important concept and forms the basis of most games you'll be writing
	// Within this loop we generally do the following things:
	//   * Check for input from the user (and do something about it!)
	//   * Update our world
	//   * Draw our world
	// We will come back to this in later lectures
	
	input GameInput;
	
	bool Quit = false;
	while(!Quit)
	{
		 //Update our world
		 //update input
		GameInput.GameInputs();
	
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
	
		// Update the model, to make it rotate
		myPlayer->Update( deltaTs, &GameInput );
		camera->update(myPlayer->GetPosition(), 1.2f);
	
		if(GameInput.isQuitDown()==true)
		{
			Quit = true;
		}

		// Draw our world
	{
		// Specify the colour to clear the framebuffer to
		glClearColor(0.0f,0.0f,0.0f,0.0f);
		// This writes the above colour to the colour part of the framebuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// Draw the object using the given view (which contains the camera orientation) and projection (which contains information about the camera 'lense')
		myPlayer->Draw( camera->getViewMatrix(), camera->getprojectionMatrix());
	
		for(int i = 0; i < CubeArray.size(); i++)
		{
			// update and draw here becasue why not
			CubeArray[i]->Update(deltaTs);
			
			if(CubeArray[i]->isOffScreen()==true)
			{
				CubeArray[i]->SetPosition(glm::vec3(CubeArray[i]->GetPosition().x, CubeArray[i]->GetPosition().y, CubeArray[i]->GetPosition().z-400));
			}
	
			CubeArray[i]->Draw(camera->getViewMatrix(), camera->getprojectionMatrix());
		}
	
		// This tells the renderer to actually show its contents to the screen
		// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
		SDL_GL_SwapWindow( window );
	}

		// Limiter in case we're running really quick
		if( deltaTs < (1.0f/50.0f) )	// not sure how accurate the SDL_Delay function is..
		{
			SDL_Delay((unsigned int) (((1.0f/50.0f) - deltaTs)*1000.0f) );
		}
	}
	// If we get outside the main game loop, it means our user has requested we exit

	// Cleanup
	SDL_GL_DeleteContext( glcontext );
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}