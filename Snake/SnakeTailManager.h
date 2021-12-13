#pragma once
#include "SnakeTail.h"
#include "DotManager.h"
class SnakeTailManager
{
	DotManager a;
	int X[2000], Y[2000];
public:
	void AddLength(SnakeTail &tail, SDL_Renderer* renderer, SnakeHead &head) {
		if (tail.length < 2000) {
			a.LoadDotTexture(tail.Tail[tail.length], renderer, "Dot.bmp");
			if (tail.length == 0) {
				tail.Tail[tail.length].SetX(head.GetX());
				tail.Tail[tail.length].SetY(head.GetY());
			}
			else {
				tail.Tail[tail.length].SetX(tail.Tail[tail.length - 1].GetX());
				tail.Tail[tail.length].SetY(tail.Tail[tail.length - 1].GetY());
			}
			tail.length++;
		}
		
	}
	void SnakeTailRender(SnakeTail &tail, SDL_Renderer* renderer) {
		for (int i = 0; i < tail.length; i++) {
			a.DotRender(tail.Tail[i], renderer);
		}
	}
	void TailClose(SnakeTail& tail) {
		for (int i = 0; i < tail.length; i++) {
			a.DotClose(tail.Tail[i]);
		}
		tail.length = 0;
	}
	void MoveTail(SnakeTail& t, SnakeHead head) {
		for (int i = 0; i < t.length; i++) {
			X[i] = t.Tail[i].GetX();
			Y[i] = t.Tail[i].GetY();
		}
		t.Tail[0].SetX(head.GetX());
		t.Tail[0].SetY(head.GetY());
		for (int i = 1; i < t.length; i++) {
			t.Tail[i].SetX(X[i - 1]);
			t.Tail[i].SetY(Y[i - 1]);
		}

	}
	SDL_Rect GetDotRect(SnakeTail *t, int i) {
		return a.DotRect(t->Tail[i]);
	}
	
	
};

