#pragma once
class SnakeHead
{
	int velx = 5, vely = 0, vel = 5, direction = 0;
	int x = 200, y = 0, width = 0, height = 0;
	SDL_Texture* SnakeHeadTexture = NULL;
	friend class SnakeHeadManager;
public:
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	int GetVelx() {
		return velx;
	}
	int GetVely() {
		return vely;
	}
	int Width() {
		return width;
	}
	int Height() {
		return height;
	}
	int Direction() {
		return direction;
	}
};


