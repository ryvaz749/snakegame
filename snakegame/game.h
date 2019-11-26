#pragma once
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"snake.h"
#include <time.h>
#include <list>
#include<stdio.h>
#include<vector>
#include "enemy.h"
#include "circulo.h"
#include <vector>
#include"rectangulo.h"
#include "enemy.h"
#include "activador.h"
#include "fuego.h"
#include "pared.h"
#include "selector.h"
#include <fstream>
/*#include "letrero.h"
class real;
class nulo;*/
class game
{
public:
	game();
	void run();
	~game();

private:
	//letrero* perder;
	ifstream file;
	ofstream filo;
	sf::View camera;
	pared p;
	string qwerty;
	void  events(), gridzise(int), fcamera(int), update(sf::Time detla), render(), inicio(), select(selector*), cual(), random(rectangulo, vector<vector<int>>*, int), renderpause(), smenu(), eliminar();
	int puntos = 0, highscores[3] = { 0,0,0 },ncamera,tamaño, velocidad = 20;
	selector niveles, menu;
	vector<pared> paredes;
	vector<enemy> enemys;
	sf::Time deltatime;
	sf::Clock clock;
	sf::RenderWindow window;
	sf::Texture ttitulo,tfondo;
	sf::Font letras;
	sf::Text press, puntacion, tvelocidad;
	circulo luz;// , portal;
	rectangulo manzana;
	vector<rectangulo> manzanas;
	sf::RectangleShape titulo,fondo,piso,nada;
	list<fuego*> disparos;
	snake jugador;
	enemy enemi;
	bool dispara,wait = true,inlevel,poner,ya=false;
	sf::Text geimover;
	bool perdiste = false,pause = false,bmenu = true;
	void input(sf::Keyboard::Key key, bool press);
	bool up, down, left, right,d = false,precionada=false,soltada=true;
	float tiempo,tdisparo,tmanzana;
	activador activ1;
	vector<vector<int>> grid;
};

