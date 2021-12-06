#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Food.h"
#include "Snake.h"
#include "FoodManager.h"
#include "SnakeManager.h"
#include "Functions.h"

const int ScreenWidth = 1600;
const int ScreenHeight = 900;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* MapTexture = NULL;

int main(int argc, char* args[]) {
	srand(time(0));
	Snake *snake = new Snake;
	SnakeManager mngr;
	Food food;
	FoodManager foodmngr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Color textcolor{ 0, 0, 0, 255 };
	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//loading map texture
	SDL_Surface* screen = NULL;
	screen = IMG_Load("map.bmp");
	SDL_Rect mapRect{ 0, 0, screen->w, screen->h };
	MapTexture = SDL_CreateTextureFromSurface(renderer, screen);
	SDL_FreeSurface(screen);
	screen = NULL;
	

	bool quit = false;
	mngr.LoadHeadTexture(*snake, renderer);
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
				mngr.ChangeSnakeVel(*snake, e);
		}
		if(frame >= 10){
			mngr.AddTailLength(*snake, renderer);
			frame = 0;
		}
		
		mngr.SnakeMove(*snake);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, MapTexture, NULL, &mapRect);
		mngr.SnakeRender(*snake, renderer);
		SDL_RenderPresent(renderer);
		frame++;
		if (mngr.TailHeadCollision(*snake)) {
			break;
		}

	}
	mngr.SnakeClose(*snake);
	foodmngr.FoodClose(food);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(MapTexture);
	MapTexture = NULL;
	renderer = NULL;
	window = NULL;
	delete snake;

	SDL_Quit();
	return 0;

}