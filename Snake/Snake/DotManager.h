#pragma once
#include <SDL_image.h>
#include "Dot.h"
class DotManager
{
public:
	void DotClose(Dot dot) {
		SDL_DestroyTexture(dot.DotTexture);
		dot.DotTexture = NULL;
	}
	void LoadDotTexture(Dot &dot, SDL_Renderer* renderer, std::string string) {
		SDL_Surface* screen = NULL;
		screen = IMG_Load(string.c_str());
		dot.width = screen->w;
		dot.height = screen->h;
		dot.DotTexture = SDL_CreateTextureFromSurface(renderer, screen);
		SDL_FreeSurface(screen);
		screen = NULL;
	}
	void DotRender(Dot dot, SDL_Renderer* renderer) {
		SDL_Rect rect{ dot.x, dot.y, dot.width, dot.height };
		SDL_RenderCopy(renderer, dot.DotTexture, NULL, &rect);
	}
};

