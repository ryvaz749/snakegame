#include "pch.h"
#include "pared.h"
#include <iostream>

pared::pared()
{
	nada.setSize({ 20, 20 });
	nada.setFillColor(sf::Color::Black);
}

void pared::setposition(int _x, int _y)//se elige la posision de la parte de hasta arriba a la izquierda de un pedaxo de pared
{
	x = _x;
	y = _y;
}
void pared::dibujar(sf::RenderWindow* window) {
	for (int a = 0; a < ptrn.size(); a++) {
		for (int e = 0; e < ptrn[a].size(); e++) {
			nada.setPosition((x + a) * 20,(y + e) * 20);
			if (ptrn[e][a] == 1) {
				window->draw(nada);
			}
		}
	}
}

void pared::poner(vector<vector<int>>* grid, vector<vector<int>> patron)//se pone en la grid la pared markandola con 3 los lugares en los que ira
{
	ptrn = patron;
	for (int a = 0; a < patron.size(); a++) {
		for (int e = 0; e < patron[a].size(); e++) {
			if (patron[a][e] == 1) {
				(*grid)[e + x][a + y] = 3;
			}
		}
	}
}

pared::~pared()
{
}
