#include "pch.h"
#include "estado1.h"
#include "snake.h"





void estado1::up(snake* a)
{
	a->direccion = 1;
}

void estado1::down(snake* a)
{
}

void estado1::left(snake* a )
{
	a->direccion = 4;
}

void estado1::right(snake* a )
{
	a->direccion = 2;
}

void estado1::update()
{
}
estado1::estado1()
{
}

estado1::~estado1()
{
}
