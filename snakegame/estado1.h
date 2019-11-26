#pragma once
#include "estado.h"
class estado1 :
	public estado
{
public:
	estado1();
	void up(snake*), down(snake*), left(snake*), right(snake*);	void update();
	~estado1();
};

