#pragma once
#include<SFML/Graphics.hpp>
#include<list>
#include<stdio.h>
using namespace std;
class snake
{
public:
	snake();
	void textura(sf::Texture* tcabeza, sf::Texture* tcuerpo, sf::Texture* tmovida, sf::Texture* tcola);
	sf::RectangleShape cabeza,pedazo,movida,cola;
	int direccion = 0,vel,ante,tamaño = 20,checks=0;
	int grid[30][30];
	virtual void update();

	bool perdiste = false;
	list<sf::RectangleShape*>::reverse_iterator a;
	list<sf::RectangleShape*> cuerpo;
	~snake();
};

