#pragma once
#include<SFML/Graphics.hpp>
#include<list>
#include<stdio.h>
#include"rectangulo.h"
#include "fuego.h"
class etsado;
using namespace std;
class snake
{
public:
	snake();
	estado actual*;
	vector<vector<int>>* grid;
	void mapa(vector<vector<int>>*);
	void textura(string, string, string, string);
	void borrar();
	void dibujar(sf::RenderWindow*);
	void agregar();
	rectangulo cabeza,pedazo,movida,cola;
	int direccion = 0,vel,ante,tamaño = 2,checks=0;
	virtual void update(int);
	bool perdiste = false/*,poder=false*/;
	list<rectangulo*>::reverse_iterator a;
	list<rectangulo*> cuerpo;
	fuego disparo;
	~snake();
};

