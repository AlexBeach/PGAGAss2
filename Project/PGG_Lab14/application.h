//#pragma once
//
//#include <SDL.h>
//#include "glew.h"
//#include <iostream>
//#include <time.h>
//#include <glm.hpp> // This is the main GLM header
//#include <gtc/type_ptr.hpp>
//#include <gtc/matrix_transform.hpp> // This one lets us use matrix transformations
//#include "input.h"
//#include "Sphere.h"
//#include "Cube.h"
//#include "Camera.h"
//
//class application
//{
//public:
//	application(void);
//	~application(void);
//
//	void Run(void);
//
//protected:
//
//	int Init();
//	void InitEntities(void);
//	void Update(float dt);
//	void Draw(float dt);
//
//private:
//
//	int winPosX, winPosY, winWidth, winHeight;
//	SDL_Window *window;
//	SDL_Renderer *renderer;
//	SDL_GLContext glcontext;
//	glm::mat4 Projection;
//	glm::mat4 View;
//
//	// call the input class to contrust object for managing game input in this game
//	input *GameInput;
//
//	Camera* camera;
//
//	//call the game entity class to create pool ball
//	Sphere *Sphere1;
//
//	std::vector<Cube*> CubeArray;
//	Cube *Cube1;
//
//	int NumOfCubes;
//
//	bool Quit;
//};