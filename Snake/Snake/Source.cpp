#include <sstream>
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
SDL_Texture* Text1 = NULL;
SDL_Texture* Text2 = NULL;
SDL_Texture* Text3 = NULL;
TTF_Font* font = NULL;

void CreateTextTexture(std::string text, SDL_Color color, SDL_Texture*& texture, SDL_Rect& rect);

int main(int argc, char* args[]) {
	srand(time(0));
	int score = 0;
	int BestScore = 0;

	std::string text1, text2;
	Snake* snake = new Snake;
	SnakeManager mngr;
	Food food;
	FoodManager foodmngr;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	TTF_Init();
	font = TTF_OpenFont("lazy.ttf", 32);
	SDL_Color textcolor{ 0, 0, 0, 255 };
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_RWops* file = SDL_RWFromFile("time.bin", "r+b");
	if (file == NULL) {
		file = SDL_RWFromFile("time.bin", "w+b");
		SDL_RWwrite(file, &BestScore, sizeof(int), 1);
		SDL_RWclose(file);
	}
	else {
		SDL_RWread(file, &BestScore, sizeof(int), 1);
		SDL_RWclose(file);
	}

	//loading map texture
	SDL_Surface* screen = NULL;
	screen = IMG_Load("map.bmp");
	SDL_Rect mapRect{ 0, 0, screen->w, screen->h };
	SDL_Rect mapCollider{ 30, 30, screen->w - 60, screen->h - 60 };
	MapTexture = SDL_CreateTextureFromSurface(renderer, screen);
	SDL_FreeSurface(screen);
	screen = NULL;

	SDL_Rect text1rect{ 0, ScreenHeight - 50, 0, 0 };
	SDL_Rect text2rect{ 400, ScreenHeight - 50, 0, 0 };
	SDL_Rect text3rect{ 450, 400, 0, 0 };


	bool quit = false;
	bool alive = true;
	SDL_Event e;
	mngr.LoadHeadTexture(*snake, renderer);
	foodmngr.LoadFoodTexture(food, renderer, "food.bmp");
	foodmngr.FoodSpawn(food);
	for (int i = 0; i < 10; i++) {
		mngr.AddTailLength(*snake, renderer);
	}
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else mngr.ChangeSnakeVel(*snake, e);
		}
		if (mngr.FoodCollision(snake->GetHead(), foodmngr.FoodRect(food))) {
			score += 10;
			for (int i = 0; i <= 10; i++) {
				mngr.AddTailLength(*snake, renderer);
			}
			foodmngr.FoodSpawn(food);
			if (score > BestScore)
				BestScore = score;
		}
		mngr.SnakeMove(*snake);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		text1 = "Current score: " + std::to_string(score);
		text2 = "Best score: " + std::to_string(BestScore);
		CreateTextTexture(text1, textcolor, Text1, text1rect);
		CreateTextTexture(text2, textcolor, Text2, text2rect);
		SDL_RenderCopy(renderer, MapTexture, NULL, &mapRect);
		SDL_RenderCopy(renderer, Text1, NULL, &text1rect);
		SDL_RenderCopy(renderer, Text2, NULL, &text2rect);
		foodmngr.FoodRender(food, renderer);
		mngr.SnakeRender(*snake, renderer);
		SDL_RenderPresent(renderer);
		if (mngr.TailCollision(snake) || !mngr.MapCollision(snake->GetHead(), mapCollider)) {
			alive = false;
			CreateTextTexture("Press Enter to restart the game", textcolor, Text3, text3rect);
			SDL_RenderCopy(renderer, Text3, NULL, &text3rect);
			SDL_RenderPresent(renderer);
		}
		while (!alive) {
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT) {
					alive = true;
					quit = true;
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
					mngr.SnakeClose(*snake);
					mngr.LoadHeadTexture(*snake, renderer);
					foodmngr.FoodSpawn(food);
					for (int i = 0; i < 10; i++) {
						mngr.AddTailLength(*snake, renderer);
					}
					mngr.SnakeSpawn(*snake);
					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(renderer);
					score = 0;
					alive = true;
				}
			}
		}
	}
	mngr.SnakeClose(*snake);
	foodmngr.FoodClose(food);
	file = SDL_RWFromFile("time.bin", "w+b");
	if (file != NULL)
	{
		SDL_RWwrite(file, &BestScore, sizeof(int), 1);
		SDL_RWclose(file);
	}


	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(MapTexture);
	SDL_DestroyTexture(Text1);
	SDL_DestroyTexture(Text2);
	SDL_DestroyTexture(Text3);
	MapTexture = NULL;
    Text1 = NULL;
	Text2 = NULL;
	Text3 = NULL;
	renderer = NULL;
	window = NULL;
	delete snake;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;

}

void CreateTextTexture(std::string text, SDL_Color color, SDL_Texture*& texture, SDL_Rect& rect) {
	SDL_Surface* screen = NULL;
	screen = SDL_GetWindowSurface(window);
	screen = TTF_RenderText_Solid(font, text.c_str(), color);
	rect.w = screen->w;
	rect.h = screen->h;
	texture = SDL_CreateTextureFromSurface(renderer, screen);
	SDL_FreeSurface(screen);
	screen = NULL;
}

