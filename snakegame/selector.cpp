#include "pch.h"
#include "selector.h"
#include <iostream>

selector::selector()
{
	letras.loadFromFile("minecraft.ttf");;
	texto.setFont(letras);
	texto.setFillColor(sf::Color(100, 100, 100));
}

void selector::render(sf::RenderWindow* window, sf::View* camera, sf::Text(uidraw)(sf::Text, sf::View*),bool up, bool down,bool wait)
{
	textos[cual].setFillColor(sf::Color(100, 100, 100));//la opcion en la que esta se pone de griz
	if (up && cual != z) {//si preciono arriba y no es el de asta arriba sube uno
		cual -= 1;
	}
	if (down && cual != textos.size() - 1) {//si preciono hacia abajo y no es el de hasta abajo baja uno
		cual += 1;
	}
	textos[cual].setFillColor(sf::Color(255, 255, 255));//brilla en el que esta
	for (int a = 0; a < textos.size(); a++) {
		window->draw(uidraw(textos[a], camera));//si el nivel fuera grande y la camara se moviera esto asegura que siempre aparesca en el mismo lugar
	}
}

void selector::lista(vector<string> li)//se le pasa una lista de string los cuales seran las opciones de la selector
{
	for (int a = 0; a < li.size(); a++) {
		textos.push_back(texto);
		textos[a].setPosition(x, y*a + 50);
		textos[a].setString(li[a]);
	}
}


selector::~selector()
{
}
