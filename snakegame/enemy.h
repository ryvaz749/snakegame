#pragma once
#include "snake.h"
#include "rectangulo.h"
class enemy :
	public snake
{
public:
	bool frente = false;
	enemy();
	int distancia(rectangulo),dis;
	void updates();
	bool detectar();
	void nuevobjetivo(vector<rectangulo>);
	void nuevamanzana(rectangulo);
	~enemy();
	rectangulo esta;
};

