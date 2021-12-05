#pragma once
#include <vector>
#include "Dot.h"
class SnakeTail
{
	Dot Tail[1000];
	int length = 0;
	friend class SnakeTailManager;
};


