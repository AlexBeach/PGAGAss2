#include "application.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

application::application(void)
{
	winPosX = 100;
	winPosY = 100;
	winWidth = 640;
	winHeight = 480;

	NumOfCubes = 100;

	GameInput = new input();
}

application::~application(void)
{
	// Cleanup phase
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow( window );
	SDL_Quit();
}

void application::Init()
{
	// This is how we set the context profile
	// We need to do this through SDL, so that it can set up the OpenGL drawing context that matches this
	// (of course in reality we have no guarantee this will be available and should provide fallback methods if it's not!)
	// Anyway, we basically first say which version of OpenGL we want to use
	// So let's say 4.3:
	// Major version number (4):
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	// Minor version number (3):
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Then we say whether we want the core profile or the compatibility profile
	// Flag options are either: SDL_GL_CONTEXT_PROFILE_CORE   or   SDL_GL_CONTEXT_PROFILE_COMPATIBILITY
	// We'll go for the core profile
	// This means we are using the latest version and cannot use the deprecated functions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	// Now we have got SDL initialised, we are ready to create a window!
	// These are some variables to help show you what the parameters are for this function
	// You can experiment with the numbers to see what they do
	window = SDL_CreateWindow("SimpleGameForPGAG",  // The first parameter is the window title
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
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Now that the SDL renderer is created for the window, we can create an OpenGL context for it!
	// This will allow us to actually use OpenGL to draw to the window
	glcontext = SDL_GL_CreateContext(window);

	// Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
	glEnable(GL_DEPTH_TEST);
}

void application::InitEntities(void)
{
	ObjectLoader *cube = new ObjectLoader("Cube.obj");

	Sphere1 = new Sphere();
	ObjectLoader *sphere = new ObjectLoader("Sphere.obj");
	Sphere1->AttachMesh(sphere);
	Sphere1->setPos(glm::vec3(-2, 0, -10));

	float x, y, z;
	x = -10;
	y = -10;
	z = -60;

	for(int i=0; i<NumOfCubes; i++)
	{
		x+=1;
		y+=1;

		Cube1 = new Cube();
		Cube1->AttachMesh(cube);
		Cube1->setPos(glm::vec3(x, y, z));

		CubeArray.push_back(Cube1);
	}
}

bool application::Update(int dt)
{
	GameInput->GameInputs(incomingEvent);

	if(GameInput->getQuit()==true)
	{
		return true;
	}

	Sphere1->Update(dt);

	for(int i=0; i<CubeArray.size(); i++)
	{
		CubeArray[i]->Update(dt);
	}

	return false;
}

void application::Draw()
{
	// Specify the colour to clear the framebuffer to
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// This writes the above colour to the colour part of the framebuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Construct a projection matrix for the camera
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 900.0f);

	// Create a viewing matrix for the camera
	// Don't forget, this is the opposite of where the camera actually is
	// You can think of this as moving the world away from the camera
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,-2.5f));

	Sphere1->Draw(View, Projection);

	for(int i=0; i<CubeArray.size(); i++)
	{
		CubeArray[i]->Draw(View, Projection);
	}

	// This tells the renderer to actually show its contents to the screen
	// We'll get into this sort of thing at a later date - or just look up 'double buffering' if you're impatient :P
	SDL_GL_SwapWindow( window );
}