#include "pch.h"
#include "snake.h"
#include <iostream>
#include "estado.h"
snake::snake()
{
	cabeza.setPosition(10, 10);
	vel = 20;
	//direccion = 1;
	//poder = false;
}
void snake::mapa(vector<vector<int>>* a)
{
	grid = a;//usan la grid para detectar lo quehay alrededor
}
void snake::textura(string tcabeza, string tcuerpo, string tmovida, string tcola) {
	// se ponen todas las texturas del cuerpo con una sola funcion
	cabeza.textura(tcabeza);
	pedazo.textura(tcuerpo);
	movida.textura(tmovida);
	cola.textura(tcola);
}

void snake::borrar()
{
	cuerpo.erase(cuerpo.begin(), cuerpo.end());//borra todo el cuerpo
}

void snake::dibujar(sf::RenderWindow* window)//dibuja todo el cuerpo
{
	window->draw(cabeza);
	for (rectangulo* a : cuerpo) {
		window->draw(*a);
	}
	window->draw(cola);
}

void snake::agregar()
{
	(*cuerpo.begin())->setPosition(cabeza.getPosition().x, cabeza.getPosition().y);
}

void snake::update(int a)
{
	
	/*if ((*grid)[x][y] == 2) {
		checks -= 1;
	}*/
	if (ante == direccion) {//si no se cambio de direccion al cuerpo se le agredara un pedazo recto con la rotacion adecuada
		cuerpo.push_front(new rectangulo(pedazo));
		agregar();
		switch (direccion) {
		case 1:
			(*cuerpo.begin())->setRotation(0);
			break;
		case 3:
			(*cuerpo.begin())->setRotation(180);
			break;
		case 2:
			(*cuerpo.begin())->setRotation(90);
			break;
		case 4:
			(*cuerpo.begin())->setRotation(270);
			break;
		}
		
	}
	else {//si se cambio la direccion ce agregara un pedazo girado, con la rotacion adecuada
		cuerpo.push_front(new rectangulo(movida));
		agregar();
		if ((ante == 1 && direccion == 4) || (ante == 2 && direccion == 3)) {
			(*cuerpo.begin())->setRotation(90);
		}
		else if ((ante == 3 && direccion == 4) || (ante == 2 && direccion == 1)) {
			(*cuerpo.begin())->setRotation(180);
		}
		else if((ante == 3 && direccion == 2) || (ante == 4 && direccion == 1)) {
			(*cuerpo.begin())->setRotation(270);
		}
	}
	cola.setPosition((*cuerpo.rbegin())->getPosition().x, (*cuerpo.rbegin())->getPosition().y);//se coloca la cola en la posision del ultimo pedazo de cuerpo
	if (cuerpo.size() == tamaño) {//si el cuerpo mide lo mismo que el tamaño que la serpiente se quita el ultimo pedazo de la serpiente
		delete *cuerpo.rbegin();
		cuerpo.pop_back();
	}
	if ((*cuerpo.rbegin())->getPosition().y < cola.getPosition().y) {
		cola.setRotation(0);
	}
	else if ((*cuerpo.rbegin())->getPosition().y > cola.getPosition().y) {
		cola.setRotation(180);
	}
	else if ((*cuerpo.rbegin())->getPosition().x < cola.getPosition().x) {
		cola.setRotation(270);
	}
	else {
		cola.setRotation(90);
	}
	//cola.setRotation((*cuerpo.rbegin())->getRotation());
	
	switch (direccion) {//dependiendo de la direccion la serpiente se movera y tendra la cabeza en esa direccion
		case 1:
			cabeza.setPosition(cabeza.getPosition().x, cabeza.getPosition().y - vel);
			cabeza.setRotation(0);
			break;
		case 3:
			cabeza.setPosition(cabeza.getPosition().x, cabeza.getPosition().y + vel);
			cabeza.setRotation(180);
			break;
		case 2:
			cabeza.setPosition(cabeza.getPosition().x+vel, cabeza.getPosition().y);
			cabeza.setRotation(90);
			break;
		case 4:
			cabeza.setPosition(cabeza.getPosition().x-vel, cabeza.getPosition().y);
			cabeza.setRotation(270);
			break;
	}
	int x = cabeza.getPosition().x / 20;
	int y = cabeza.getPosition().y / 20;
	if (x < 0 || y < 0 || x == a-1 || y == a-1) {//si te sales de la grid pierdes
		perdiste = true;
	}
	/*if () {
		yi = 580 - yi;
	}
	cabeza.setPosition(xi % 600, yi % 600);*/
	ante = direccion;//guarda la posision para que en el proximo loop sea la anterion
	if ((*grid)[x][y] % 2 == 1) {//
		perdiste = true;
	}
	/*if ((*grid)[x][y] > 1) {
		checks += 1;
	}*/
	(*grid)[x][y] += 1;
	x = cola.getPosition().x / 20;
	y = cola.getPosition().y / 20;
	(*grid)[x][y] -= 1;
}

snake::~snake()
{
}
