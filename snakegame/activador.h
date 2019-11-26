#pragma once
#include <vector>
#include <stdio.h>
#include "circulo.h"
#include <list>
#include "circulo.h"
#include "rectangulo.h"
#include "snake.h"
#include "SFML/Graphics.hpp"
using namespace std;
class activador
{
public:
	activador();
	list<circulo*> luzes;
	circulo luz;
	rectangulo poder;
	vector<vector<int>>* grid;
	void update(snake*),dibujar(sf::RenderWindow*);
	void mapa(vector<vector<int>>*);
	void goal(int x, int y, vector<vector<int>> patron);
	int checks = 0;
	bool ya = false,pri = true;
	~activador();
};

