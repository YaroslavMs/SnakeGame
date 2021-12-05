#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "SnakeHead.h"
class SnakeHeadManager
{
public:
	void HeadClose(SnakeHead &head) {
		SDL_DestroyTexture(head.SnakeHeadTexture);
		head.SnakeHeadTexture = NULL;
	}
	void LoadHeadTexture(SnakeHead &head, SDL_Renderer* renderer, std::string string) {
		SDL_Surface* screen = NULL;
		screen = IMG_Load(string.c_str());
		head.width = screen->w;
		head.height = screen->h;
		head.SnakeHeadTexture = SDL_CreateTextureFromSurface(renderer, screen);
		SDL_FreeSurface(screen);
		screen = NULL;
	}
	void HeadRender(SnakeHead head, SDL_Renderer* renderer) {
		SDL_Rect rect{ head.x, head.y, head.width, head.height };
		SDL_RenderCopy(renderer, head.SnakeHeadTexture, NULL, &rect);
	}
	void ChangeHeadVel(SnakeHead &head, SDL_Event& e) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
			if (head.vely == 0) {
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: head.vely = -head.vel; head.velx = 0; head.direction = -1; break;
				case SDLK_DOWN: head.vely = +head.vel; head.velx = 0; head.direction = 1; break;
				}
			}
			 if (head.velx == 0) {
				switch (e.key.keysym.sym)
				{
			    case SDLK_LEFT: head.velx = -head.vel; head.vely = 0; head.direction = -2; break;
			    case SDLK_RIGHT: head.velx = +head.vel; head.vely = 0; head.direction = 2; break;
				}
			}
		}
	}
	void MoveHead(SnakeHead& head) {
		head.x += head.velx;
		head.y += head.vely;
	}
};

