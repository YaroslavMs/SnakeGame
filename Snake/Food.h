#pragma once
#include <SDL.h>
#include <string>
class Food
{
	int x = 0, y = 0, width = 0, height = 0;
	SDL_Texture* FoodTexture = NULL;
	friend class FoodManager;
};


