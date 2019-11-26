#pragma once
#include "letrero.h"
class nulo :
	public letrero
{
public:
	nulo();
	nulo(letrero*);
	void dibujar(sf::RenderWindow*);
	~nulo();
};

