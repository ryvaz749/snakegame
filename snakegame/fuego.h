#pragma once
#include "circulo.h"
#include "rectangulo.h"
#include "SFML/Graphics.hpp"
class fuego
{
public:
	fuego();
	circulo bola;
	rectangulo incendio;
	void dibujar(sf::RenderWindow*);
	int direccion, paso = 0;
	bool ya = false,no = false;
	void update();
	~fuego();
};

