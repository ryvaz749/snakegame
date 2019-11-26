
#include "pch.h"
#include "activador.h"
#include <ctime> 
#include <iostream>
activador::activador()
{
	poder.textura("power.png");
	srand(time(NULL));
	luz.textura("luz.png");
}

void activador::update(snake* jugador)
{
	for (list<circulo*>::iterator a = luzes.begin(); a != luzes.end(); a++) {
		if ((*a)->getPosition() == jugador->cabeza.getPosition()) {
			checks += 1;
		}
		if ((*a)->getPosition() == jugador->cola.getPosition()) {
			checks -= 1;
		}
	}
	if (checks == luzes.size() && pri == true) {
		pri = false;
		poder.setPosition(((rand() % 20) + 1) * 20 - 10, ((rand() % 20) + 1) * 20 - 10);
		ya = true;
	}
}

void activador::dibujar(sf::RenderWindow *window)
{
	for (list<circulo*>::iterator a = luzes.begin(); a != luzes.end(); a++) {
		window->draw((*(*a)));
	}
	if (ya == true) {
		window->draw(poder);
	}
}

void activador::mapa(vector<vector<int>>* a)
{
	grid = a;
}

void activador::goal(int x, int y, vector<vector<int>> patron)
{
	for (int a = 0; a < patron.size(); a++) {
		for (int e = 0; e < patron[a].size(); e++) {
			if (patron[a][e] == 1) {
				luzes.push_front(new circulo(luz));
				(*luzes.begin())->setPosition((e + x) * 20 + 10, (a + y) * 20 + 10);
			}
		}
	}
}


activador::~activador()
{
}
