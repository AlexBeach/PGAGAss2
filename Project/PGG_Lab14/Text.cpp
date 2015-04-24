#include "Text.h"

Text::Text(void)
{
	// Initialise SDL_ttf library
   if (TTF_Init() != 0)
   {
      std::cerr << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
      SDL_Quit();
      exit(1);
   }

	font1 = TTF_OpenFont("Text/Anonymous.ttf", 12);
	font2 = TTF_OpenFont("Text/Anonymous.ttf", 36);

	if (font1 == NULL)
	{
	   std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
	   TTF_Quit();
	   SDL_Quit();
	   exit(1);
	}

	if (font2 == NULL)
	{
	   std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
	   TTF_Quit();
	   SDL_Quit();
	   exit(1);
	}
	
	text_colour.r = 255;
	text_colour.g = 255;
	text_colour.b = 255;
	text_colour.a = 255;

	mTexture = NULL;
}

Text::~Text(void)
{
	TTF_CloseFont(font1);
	font1 = NULL;

	TTF_CloseFont(font2);
	font2 = NULL;

	// Shutdown the TTF library
   TTF_Quit();
}

void Text::drawText(std::string text, int PosX, int PosY, SDL_Renderer* renderer, int fontnum)
{
	// Write text to surface
	SDL_Colour bg_colour = {0,0,0};
	if(fontnum==1)
	{
		surface = TTF_RenderText(font1, text.c_str(), text_colour, bg_colour);
	}
	else if (fontnum==2)
	{
		surface = TTF_RenderText(font2, text.c_str(), text_colour, bg_colour);
	}

	mTexture =  SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	//Destination
	SDL_Rect destRect;
	destRect.x = PosX;
	destRect.y = PosY;

	//Query the texture to get original width and height
	SDL_QueryTexture(mTexture, NULL, NULL, &destRect.w, &destRect.h);

	//Copy the texture memory onto the screen (The null parameter is used to specify a section of the image to display (rectangle again), eg. sprite sheets)
	SDL_RenderCopy(renderer, mTexture, NULL, &destRect);

	SDL_DestroyTexture(mTexture);
}