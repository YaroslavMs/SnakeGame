#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Food.h"
#include "Snake.h"
#include "FoodManager.h"
#include "SnakeManager.h"

const int ScreenWidth = 1600;
const int ScreenHeight = 900;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* args[]) {
	srand(time(0));
	Snake snake;
	SnakeManager mngr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Color textcolor{ 0, 0, 0, 255 };
	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	bool quit = false;
	mngr.LoadHeadTexture(snake, renderer);
	for (int i = 0; i < 200; i++) {
		mngr.AddTailLength(snake, renderer);
	}
	SDL_Event e;
	int frame = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else
				mngr.ChangeSnakeVel(snake, e);
		}
		mngr.SnakeMove(snake);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		mngr.SnakeRender(snake, renderer);
		SDL_RenderPresent(renderer);
		frame++;

	}
	mngr.SnakeClose(snake);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	SDL_Quit();
	return 0;

}