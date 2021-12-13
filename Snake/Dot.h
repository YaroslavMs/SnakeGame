#pragma once
#include <string>
#include <SDL.h>


class Dot
{
	int x = -100, y = -100, width = 0, height = 0;
	SDL_Texture* DotTexture = NULL;
	friend class DotManager;
public:
	void SetX(int x) {
		this->x = x;
	}
	void SetY(int y) {
		this->y = y;
	}
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	int GetWidth() {
		return width;
	}
	int GetHeight() {
		return height;
	}
};