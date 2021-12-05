#pragma once
#include <time.h>
#include <SDL_image.h>
#include "Food.h"
class FoodManager
{
public:
	void FoodClose(Food &food) {
		SDL_DestroyTexture(food.FoodTexture);
		food.FoodTexture = NULL;
	}
    void LoadFoodTexture(Food &food, SDL_Renderer* renderer, std::string string) {
		SDL_Surface* screen = NULL;
		screen = IMG_Load(string.c_str());
		food.width = screen->w;
		food.height = screen->h;
		food.FoodTexture = SDL_CreateTextureFromSurface(renderer, screen);
		SDL_FreeSurface(screen);
		screen = NULL;
	}
	void FoodSpawn(Food &food) {
		food.x = rand() % 1550;
		food.y = rand() % 850;
	}
	void FoodRender(Food food, SDL_Renderer* renderer) {
		SDL_Rect rect{ food.x, food.y, food.width, food.height };
		SDL_RenderCopy(renderer, food.FoodTexture, NULL, &rect);
	}
};

