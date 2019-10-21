#pragma once
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"snake.h"
#include <time.h>
#include <list>
#include<stdio.h>
#include<vector>
#include "enemy.h"
class game
{
public:
	game();
	void run();
	~game();
	void goal(int x, int y, vector<vector<int>> patron);
private:
	enemy esta;
	void events(), update(sf::Time detla), render();
	sf::RenderWindow window;
	sf::Texture tcabeza,tcuerpo,tmovida,tcola,tmanzana,tluz,tportal;
	sf::RectangleShape manzana;
	sf::CircleShape luz,portal;
	snake jugador;
	list<sf::CircleShape*> luzes;
	bool open = false;
	sf::Text geimover;
	bool perdiste = false;
	void input(sf::Keyboard::Key key, bool press);
	bool up, down, left, right;
	float tiempo;

	//snake jugador;
};

