#pragma once

#include <SDL.h>
#include "glew.h"
#include <iostream>
#include <time.h>
#include <glm.hpp> // This is the main GLM header
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations/#include "Mesh.h"
//#include "ObjectLoader.h"
#include "Mesh.h"
#include "input.h"
#include "GameEntity.h"
#include "Sphere.h"
#include "Cube.h"
#include "Camera.h"

class application
{
public:
	application(void);
	~application(void);

	void Run(void);

private:

	int Init();
	void InitEntities(void);
	void Update(float dt);
	void Draw(float dt);

	int winPosX, winPosY, winWidth, winHeight;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_GLContext glcontext;
	glm::mat4 Projection;
	glm::mat4 View;

	// call the input class to contrust object for managing game input in this game
	input GameInput;

	Mesh* playerMesh;
	Mesh* CubeMesh;
	Camera* camera;

	//call the game entity class to create pool ball
	Sphere *myPlayer;

	std::vector<Cube*> CubeArray;

	int NumOfCubes;

	bool Quit;
};