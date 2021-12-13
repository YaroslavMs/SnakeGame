#pragma once
class SnakeHead
{
	int velx = 7, vely = 0, vel = 7, direction = 0;
	int x = 700, y = 350, width = 0, height = 0;
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


