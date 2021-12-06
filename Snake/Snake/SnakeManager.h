#pragma once
#include "Functions.h"
#include "Snake.h"
#include "SnakeHeadManager.h"
#include "SnakeTailManager.h"
class SnakeManager
{
	SnakeHeadManager a;
	SnakeTailManager b;

public:
	void SnakeSpawn(Snake& snake) {
		a.Spawn(snake.head);
	}
	void SnakeRender(Snake &snake, SDL_Renderer* renderer) {
		a.HeadRender(snake.head, renderer);
		b.SnakeTailRender(snake.tail, renderer);
	}
	void SnakeMove(Snake& snake) {
		a.MoveHead(snake.head);
		b.MoveTail(snake.tail, snake.head);
	}
	void LoadHeadTexture(Snake& snake, SDL_Renderer* renderer) {
		a.LoadHeadTexture(snake.head, renderer, "Dot.bmp");
	}
	void AddTailLength(Snake& snake, SDL_Renderer* renderer) {
		b.AddLength(snake.tail, renderer, snake.head);
	}
	void ChangeSnakeVel(Snake& snake, SDL_Event &e) {
		a.ChangeHeadVel(snake.head, e);
	}
	void SnakeClose(Snake& snake) {
		a.HeadClose(snake.head);
		b.TailClose(snake.tail);
	}
	bool TailCollision(Snake *snake) {
		for (int i = 20; i < snake->tail.Length(); i++) {
			if (Collider(a.HeadRect(snake->head), b.GetDotRect(&(snake->tail), i))) {
				return true;
			}
		}
		return false;
	}
	bool MapCollision(SnakeHead head, SDL_Rect Map) {
		return Collider(a.HeadRect(head), Map);
	}
	bool FoodCollision(SnakeHead head, SDL_Rect food) {
		return Collider(a.HeadRect(head), food);
	}
};

