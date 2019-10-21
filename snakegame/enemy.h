#pragma once
#include "snake.h"
class enemy :
	public snake
{
public:
	enemy();
	virtual void update();
	~enemy();
};

