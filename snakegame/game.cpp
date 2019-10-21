#include "pch.h"
#include "game.h"
#include "snake.h"
#include<list>
#include<stdio.h>
#include <cstdlib> 
#include <ctime> 
#include<iostream>
using namespace std;
game::game() : window(sf::VideoMode(600, 600), "snakegame"), jugador()
{
	srand(time(NULL));
	tiempo = 0;
	geimover.setString("TEMORRISTE");
	geimover.setPosition(150, 300);
	geimover.setCharacterSize(50);
	geimover.setFillColor(sf::Color::Cyan);
	tcabeza.loadFromFile("cabeza.png");
	tcuerpo.loadFromFile("cuerpo.png");
	tmovida.loadFromFile("movida.png");
	tcola.loadFromFile("cola.png");
	tmanzana.loadFromFile("manzana.png");
	tluz.loadFromFile("luz.png");
	tportal.loadFromFile("portal.png");
	portal.setTexture(&tportal);
	portal.setRadius(10);
	portal.setOrigin(10, 10);
	portal.setPosition(10, 10);
	luz.setTexture(&tluz);
	luz.setOrigin(10, 10);
	luz.setRadius(10);
	manzana.setTexture(&tmanzana);
	manzana.setPosition(((rand()%20)+1)*20-10, ((rand() % 20) + 1) * 20 - 10);
	manzana.setSize(sf::Vector2<float>(20, 20));
	manzana.setOrigin(10, 10);
	jugador.textura(&tcabeza,&tcuerpo,&tmovida,&tcola);
	up = false;
	down = false;
	left = false;
	esta.update();
	/*jugador.setPosition(100, 100);
	jugador.setSize(sf::Vector2<float>(100,100));
	jugador.setTexture(&tcabeza);*/
}

void game::run() {
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Time deltatime = clock.restart();
		events();
		if (jugador.perdiste == false) {
			update(deltatime);
			
		}
		render();
	}
}

game::~game()
{
}
void game::goal(int x, int y, vector<vector<int>> patron)
{
	for (int a = 0; a < patron.size(); a++) {
		for (int e = 0; e < patron[a].size(); e++) {
			if (patron[a][e] == 1) {
				luzes.push_front(new sf::CircleShape(luz));
				jugador.grid[e+x][a+y] = 2;
				(*luzes.begin())->setPosition((e+x) * 20+10, (a+y) * 20+10);
			}
		}
	}
}
void game::input(sf::Keyboard::Key key, bool press) {
	switch (key) {
	case sf::Keyboard::W:
		up = press;
		break;
	case sf::Keyboard::S:
		down = press;
		break;
	case sf::Keyboard::A:
		left = press;
		break;
	case sf::Keyboard::D:
		right = press;
		break;
	}
}
void game::events()
{
	sf::Event event;
	
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				input(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				input(event.key.code, false);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}

		}
}


void game::update(sf::Time dela)
{
	if (jugador.checks == luzes.size()) {
		open = true;
	}
	if (up == true && jugador.direccion != 2) {
		jugador.direccion = 1;
	}
	if (down == true && jugador.direccion != 1) {
		jugador.direccion = 2;
	}
	if (right == true && jugador.direccion != 4) {
		jugador.direccion = 3;
	}
	if (left == true && jugador.direccion != 3) {
		jugador.direccion = 4;
	}
	tiempo += dela.asSeconds();
	if (tiempo > .2f) {
		tiempo = 0;
		jugador.update();
	}
	if (manzana.getPosition() == jugador.cabeza.getPosition()) {
		manzana.setPosition(((rand() % 20) + 1) * 20 - 10, ((rand() % 20) + 1) * 20 - 10);
		jugador.tamaño += 1;
	}
}

void game::render()
{	
	window.clear();
	for (list<sf::CircleShape*>::iterator a = luzes.begin(); a != luzes.end(); a++) {
		window.draw((*(*a)));
	}
	if (open == true) {
		window.draw(portal);
	}
	window.draw(manzana);
	window.draw(jugador.cabeza);
	for (list<sf::RectangleShape*>::iterator a = jugador.cuerpo.begin(); a != jugador.cuerpo.end();a++) {
		window.draw((*(*a)));
	}
	
	window.draw(jugador.cola);
	if (jugador.perdiste == true) {
		window.draw(geimover);
	}

	window.display();
}
