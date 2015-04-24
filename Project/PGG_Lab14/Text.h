#ifndef _TEXT_H_
#define _TEXT_H_

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <string.h>

class Text
{
public:

	//Initialises variables
    Text(void);

    //Deallocates memory
    ~Text(void);

	void drawText(std::string text, int PosX, int PosY, SDL_Renderer* renderder, int fontnum);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	SDL_Surface *surface;

	SDL_Colour text_colour;

   // Load a font
   TTF_Font *font1, *font2;
};
#endif