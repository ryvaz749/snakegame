#include "pch.h"
#include "snake.h"
#include <iostream>

snake::snake()
{
	cabeza.setPosition(10, 10);
	cabeza.setSize(sf::Vector2<float>(20, 20));
	vel = 20;
	cabeza.setOrigin(10, 10);
	pedazo.setSize(sf::Vector2<float>(20, 20));
	pedazo.setOrigin(10, 10);
	movida.setSize(sf::Vector2<float>(20, 20));
	movida.setOrigin(10, 10);
	cola.setSize(sf::Vector2<float>(20, 20));
	cola.setOrigin(10, 10);
}
void snake::textura(sf::Texture* tcabeza, sf::Texture* tcuerpo, sf::Texture* tmovida, sf::Texture* tcola) {
	cabeza.setTexture(tcabeza);
	pedazo.setTexture(tcuerpo);
	movida.setTexture(tmovida);
	cola.setTexture(tcola);
}

void snake::update()
{
	cout << 'o';
	int x = cabeza.getPosition().x/20;
	int y = cabeza.getPosition().y/20;
	//cout << grid[x][y]<<endl;
	if (grid[x][y] % 2 == 1) {
		perdiste = true;
	}
	if (grid[x][y] > 1) {
		checks += 1;
	}
	grid[x][y] += 1;
	 x = cola.getPosition().x/20;
	 y = cola.getPosition().y/20;
	 grid[x][y] -= 1;
	 if (grid[x][y] == 2) {
		 checks -= 1;
	 }
	if (ante == direccion ) {
		cuerpo.push_front(new sf::RectangleShape(pedazo));
		(*cuerpo.begin())->setPosition(cabeza.getPosition().x, cabeza.getPosition().y);
		switch (direccion) {
		case 1:
			(*cuerpo.begin())->setRotation(0);
			break;
		case 2:
			(*cuerpo.begin())->setRotation(180);
			break;
		case 3:
			(*cuerpo.begin())->setRotation(90);
			break;
		case 4:
			(*cuerpo.begin())->setRotation(270);
			break;
		}
		
	}
	else {
		cuerpo.push_front(new sf::RectangleShape(movida));
		(*cuerpo.begin())->setPosition(cabeza.getPosition().x, cabeza.getPosition().y);
		if ((ante == 1 && direccion == 4) || (ante == 3 && direccion == 2)) {
			(*cuerpo.begin())->setRotation(90);
		}
		else if ((ante == 2 && direccion == 4) || (ante == 3 && direccion == 1)) {
			(*cuerpo.begin())->setRotation(180);
		}
		else if((ante == 2 && direccion == 3) || (ante == 4 && direccion == 1)) {
			(*cuerpo.begin())->setRotation(270);
		}
	}
	cola.setPosition((*cuerpo.rbegin())->getPosition().x, (*cuerpo.rbegin())->getPosition().y);
	if (cuerpo.size() == tamaño) {
		delete *cuerpo.rbegin();
		cuerpo.pop_back();
	}
	cola.setRotation((*cuerpo.rbegin())->getRotation());
	switch (direccion) {
		case 1:
			cabeza.setPosition(cabeza.getPosition().x, cabeza.getPosition().y - vel);
			cabeza.setRotation(0);
			break;
		case 2:
			cabeza.setPosition(cabeza.getPosition().x, cabeza.getPosition().y + vel);
			cabeza.setRotation(180);
			break;
		case 3:
			cabeza.setPosition(cabeza.getPosition().x+vel, cabeza.getPosition().y);
			cabeza.setRotation(90);
			break;
		case 4:
			cabeza.setPosition(cabeza.getPosition().x-vel, cabeza.getPosition().y);
			cabeza.setRotation(270);
			break;
	}
	int xi = cabeza.getPosition().x;
	int yi = cabeza.getPosition().y;
	cabeza.setPosition(xi % 600, yi % 600);
	ante = direccion;
	
}

snake::~snake()
{
}
