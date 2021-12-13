#pragma once
#include "SnakeHead.h"
#include "SnakeTail.h"

class Snake
{
	SnakeHead head;
	SnakeTail tail;
	friend class SnakeManager;
public:
	SnakeHead GetHead() {
		return head;
	}
	SnakeTail GetTail() {
		return tail;
	}

};


