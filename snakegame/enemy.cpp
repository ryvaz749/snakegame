#include "pch.h"
#include "enemy.h"
#include <iostream>
#include <cstdlib> 
#include <algorithm>
enemy::enemy()
{
	direccion = 1;
	tamaño = 5;
	srand(time(NULL));
	perdiste = false;
}

int enemy::distancia(rectangulo a)
{
	return abs(cabeza.getPosition().x - a.getPosition().x) + abs(cabeza.getPosition().y - a.getPosition().y);
	int e = cabeza.getPosition().x - a.getPosition().x;
	int i = cabeza.getPosition().y - a.getPosition().y;
	if (abs(e) < abs(i)) {
		if (e < 0) {
			return -e;
		}
		else {
			return e;
		}
	}
	else {
		if (i < 0) {
			return -i;
		}
		else {
			return i;
		}
	}
}

void enemy::updates()
{
	int e = cabeza.getPosition().x - esta.getPosition().x;
	int i = cabeza.getPosition().y - esta.getPosition().y;
	if (e == dis) {
		direccion = 4;
	}
	else if (-e == dis) {
		direccion = 2;
	}
	else if (i == dis) {
		direccion = 3;
	}
	else if (-i == dis) {
		direccion = 1;
	}
	/*if (rand() % 9 == 0 || detectar()) {
		int esta = rand() % 2;
		if (esta == 0) {
			direccion = (direccion % 5) + 1;
			if (detectar()) {
				direccion = (direccion + 3) % 5 + 1;
			}
		}
		else {
			direccion = (direccion+3)%5+1;
			if (detectar()) {
				direccion = (direccion % 5) + 1;
			}
		}
	}*/
	update(grid->size());
}

bool enemy::detectar()
{
	int x = cabeza.getPosition().x / 20;
	int y = cabeza.getPosition().y / 20;
	switch (direccion) {
	case 1:
		if (y == 0 || (y != 0 && (*grid)[x][y - 1] % 2 == 1)) {
			return true;
		}
		break;
	case 3:
		if (y == grid->size() - 1 || (y != grid->size() - 1 && (*grid)[x][y + 1] % 2 == 1)) {
			return true;
		}
		break;
	case 2:
		if (x == 0 || (x != 0 && (*grid)[x - 1][y] % 2 == 1)) {
			return true;
		}
		break;
	case 4:
		if (x == grid->size() - 1 || (x != grid->size() - 1 && (*grid)[x + 1][y] % 2 == 1)) {
			return true;
		}
		break;
	}
	return false;
}

void enemy::nuevobjetivo(vector<rectangulo> manzanas)
{
	esta = manzanas[0];
	dis = distancia(esta);
	for (rectangulo a : manzanas) {
		nuevamanzana(a);
	}
}

void enemy::nuevamanzana(rectangulo a)
{
	if (dis > distancia(a)) {
		esta = a;
		dis = distancia(esta);
	}
}


enemy::~enemy()
{
}
