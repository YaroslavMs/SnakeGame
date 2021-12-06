#pragma once
#include <vector>
#include "Dot.h"
class SnakeTail
{
	Dot Tail [1500];
	int length = 0;
	friend class SnakeTailManager;
public:
	int Length() {
		return length;
	}
};


