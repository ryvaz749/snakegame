#include "pch.h"
#include "game.h"
#include "snake.h"
#include<list>
#include<stdio.h>
#include <cstdlib> 
#include <ctime> 
#include<iostream>
/*#include "real.h"
#include "nulo.h"*/
using namespace std;
auto uidraw = [](sf::Text x, sf::View* camera) {x.setPosition(x.getPosition().x + camera->getCenter().x - 310, x.getPosition().y + camera->getCenter().y - 310); return x; };
game::game() : window(sf::VideoMode(620, 620), "snakegame"), jugador(), camera(sf::FloatRect(0, 0, 600.f, 600.f))//,enemi()
{
	file.open("test.txt");//abro el archivo donde estan guardados los highscores
	string esta;
	file >> esta;//paso el texto que esta en el archivo a esta variable
	int e = 0;
	for (int a = 0; a < 3; a++) {// como son tres highscores lo are tres veses
		qwerty = "";
		while (esta[e] != '-') {//almaseno los chars hasta que se acaba el numero, que es con un -
			qwerty += esta[e];
			e += 1;
		}
		e += 1;
		highscores[a] = stoi(qwerty);//combierto el string obtenido a int y lo igualo a su highscorecorrespondiente
	}
	file.close();
	srand(time(NULL));
	window.setView(camera);
	piso.setSize({ 20,20 });
	nada.setSize({ 20,20 });
	piso.setFillColor(sf::Color(171, 145, 68));
	string nomas = "nivel";
	ttitulo.loadFromFile("titulo.png");
	titulo.setTexture(&ttitulo);
	titulo.setPosition({ 50,100 });
	titulo.setSize({ 500,250 });
	letras.loadFromFile("minecraft.ttf");
	press.setFont(letras);
	press.setFillColor(sf::Color::White);
	/*perder->texto = press;
	perder->texto.setPosition(300, 20);*/
	//perder = new nulo(perder);
	puntacion.setFont(letras);
	puntacion.setPosition(550, 20);

	press.setString("press enter");
	tvelocidad.setFont(letras);
	tvelocidad.setFillColor(sf::Color::White);
	tvelocidad.setPosition({ 20,200 });
	press.setPosition({ 225,400 });
	tfondo.loadFromFile("piso.jpg");
	fondo.setTexture(&tfondo);
	fondo.setSize({ 60,60 });
	niveles.x = 20;
	menu.x = 200;
	niveles.y = 50;
	menu.y = 100;
	menu.lista({ "resume","restart","end game" });
	
	jugador.tamaño = 20;
	//enemi.tamaño = 8;
	tiempo = 0;
	
	enemi.mapa(&grid);
//	portal.textura("portal.png");
	luz.textura("luz.png");
	manzana.textura("manzana.png");
	manzanas.push_back(manzana);
	manzanas[0].setPosition(((rand() % 30) + 1) * 20 - 10, ((rand() % 30) + 1) * 20 - 10);
	jugador.textura("cabeza.png", "cuerpo.png", "movida.png", "cola.png");
	enemi.textura("ecabeza.png", "ecuerpo.png", "emovida.png", "ecola.png");
	up = false;
	down = false;
	left = false;
	enemi.cabeza.setPosition(110, 110);
	/*jugador.setPosition(100, 100);
	jugador.setSize(sf::Vector2<float>(100,100));
	jugador.setTexture(&tcabeza);*/
}

void game::run() {
	inicio();//la pantalla de inicio
	while (window.isOpen()) {
		up = false;
		down = false;
		dispara = false;
		events();
		camera.setCenter(310, 310);
		window.setView(camera);
		niveles.z = 0;//el seleccionador de niveles estara con la primera opcion seleccionada
		niveles.lista({ "normal        high score " + to_string(highscores[0]),"muros         high score " + to_string(highscores[1]),"enemigos    high score " + to_string(highscores[2]) });// se muestra el tipo de nivel con su highscore
		bmenu = true;
		window.clear();
		niveles.cual = 0;//el seleccionador de niveles estara con la primera opcion seleccionada
		select(&niveles);//se selecciona el nivel que se jugara
		cual();//dependiendo del nivel elegido se pondran las posisiones iniciales de los objetos del nivel
		menu.textos[0].setString("resume");//la primera pcion del menu sera resumir
		menu.z = 0;//el seleccionador del menu estara con la primera opcion seleccionada
		while (inlevel) {//mientras este dentro de un nivel
			events();
			if (!pause) {//si el juego no esta en pausa
				deltatime = clock.restart();
				if (!jugador.perdiste) {//si no a perdido
					update(deltatime);//se hace el update del juego
					render();//se renderisa
				}
				else {//si ya perdio
					pause = true;//el juego se pausa
					menu.textos[0].setString("");//la opcion de resumir desaparese
					menu.z = 1;//como no hay primera opcion el seleccionador estara en la segunda opcion
					if (highscores[niveles.cual] < puntos) {//si izo un nuevo record
						highscores[niveles.cual] = puntos;//los puntos que izo seran el highscore
					}
				}
			}
			else {//si el juego esta en pausa
				dispara = false;
				bmenu = false;
				menu.cual = 0;//el seleccionador del menu estara con la primera opcion seleccionada
				if (jugador.perdiste) {
					menu.cual = 1;//si perdio no hay primera opcion, asi que esta estara en la segunda
				}
				select(&menu);//se elige que opcion del menu se elegira
				smenu();//los efectos de lo que selecciono
				jugador.perdiste = false;//despues de esto el jugador ya n esta en el estado perder
				menu.textos[0].setString("resume");//por lo que resume vuelve a aparecer
				menu.z = 0;
			}
		}
	}
}
void game::inicio()
{
	window.draw(titulo);//en la pantaya de inicio se dibuja el titulo
	window.draw(press);//el boton al que te pide que le piques para continuar
	window.display();
	while (true) {//la pantaya de titulo estara hay hasta que le piques a algo
		events();
		if (dispara) {
			break;
		}
	}
	window.clear();
	window.display();
}

void game::select(selector* lista)//se elige una opcion de la lista que se a mandado
{
	while(true){
		//se asegura de que todos los movimientos esten en falso para que no se mueva de mas
		left = false;
		right = false;
		down = false;
		up = false;
		events();
		window.clear();
		if (inlevel) {//si esta en un nivel dibujara el nivel de fondo
			render();
		}
		if (dispara) {//cuando se elige una opcion sale del select
			break;
		}
		/*tiempo += clock.restart().asSeconds();
		if (tiempo > .4f) {
			tiempo = 0;
			wait = true;
		}*/
		if (!inlevel) {//si no esta en un nivel esta el seleccionado de velocidad 
			if (left && velocidad != 5) {
				velocidad -= 1;
			}
			if (right) {
				velocidad += 1;
			}
			tvelocidad.setString("velocidad: " + to_string(velocidad));
			window.draw(tvelocidad);
		}
		lista->render(&window,&camera,uidraw,up,down,wait);//se renderisa la lista
		window.display();
	}	
	inlevel = true;
	lista->textos[lista->cual].setFillColor(sf::Color(100, 100, 100, 255));//el texto que estaba en blanco se pone de gris para que todos sean grises
}

void game::eliminar()
{
	jugador.borrar();//se borrael jugador
	for (int a = 0; a < grid.size(); a++) {//se borra todo lo que habia en la grid
		for (int e = 0; e < grid.size(); e++) {
			grid[a][e] = 0;

		}
	}
	pause = false;//se despausa
}
void game::fcamera(int a)
{
	switch (jugador.direccion)
	{
	case 1:
		camera.move(0, -a);
		break;
	case 3:
		camera.move(0, a);
		break;
	case 2:
		camera.move(a, 0);
		break;
	case 4:
		camera.move(-a, 0);
		break;
	}
}
void game::gridzise(int e)//se reajusta el tamaño de la grid, siempre sera cuadrada
{
	grid.resize(e);
	for (int a = 0; a < e; a++) {
		grid[a].resize(e);
	}
	jugador.mapa(&grid);//se le pasa la grid al jugador
}
void game::smenu()
{
	switch (menu.cual) {//dependiendo de que se aya escogido en el menu
	case 0://si fue reanudar solo se quita la pausa
		pause = false;
		break;
	case 1://si fue reiniciar
		cual();//se buelve a crear el misno nivel en el que estaba
		break;
	case 2:// si fue salir
        inlevel = false;//ya no esta en el nivel
		break;
	}
	
}
void game::cual()// al eligir a cual nivel ir
{
	eliminar();//se elimina todo lo que habia en el nivel
	puntos = 0;//lleva 0 puntos
	jugador.direccion = 1;//su direccion siempre sera para arriva
	paredes.clear();//se borra todas las paredes que hay
	enemys.clear();//se borra todos los enemigos que hay
	
	switch (niveles.cual)//depende del nivel que aparecio
	{
	case 0://el normal
		jugador.tamaño = 4;//el jugador empieza de tamaño 4
		gridzise(31);//la grid es de 31*31
		jugador.cabeza.setPosition(310, 310);//su posision inicial es en el centro
		ncamera = 0;
		break;
	case 1://con paredes
		jugador.cabeza.setPosition(310, 310);
		jugador.tamaño = 3;
		gridzise(31);
		paredes.push_back(p);
		paredes[0].setposition(5, 5);
		paredes[0].poner(&grid, {//con el patron de facade cree un sistema para que se pongan las paredes con 1 formando la figura que tendria la pared
			{1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1}
			}
		);
		paredes.push_back(p);
		paredes[1].setposition(16, 5);
		paredes[1].poner(&grid, {
			{1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1}
			}
		);
		break;
	case 2://este esta en fase de desarrollo todavia
		jugador.tamaño = 3;
		gridzise(31);
		jugador.cabeza.setPosition(310, 310);
		ncamera = 0;
		enemys.push_back(enemi);
		enemys[0].nuevobjetivo(manzanas);
	default:
		break;
	}
}
game::~game()
{
	
}
void game::input(sf::Keyboard::Key key, bool press) {
	switch (key) {//se le permite al jugador moverse con las flechas o con wasd
	case sf::Keyboard::W:
	case sf::Keyboard::Up:
		up = press;
		break;
	case sf::Keyboard::S:
	case sf::Keyboard::Down:
		down = press;
		break;
	case sf::Keyboard::A:
	case sf::Keyboard::Left:
		left = press;
		break;
	case sf::Keyboard::D:
	case sf::Keyboard::Right:
		right = press;
		break;
	case sf::Keyboard::P:
		if (press) {
			pause = true;
		}
	case sf::Keyboard::Enter:
		dispara = press;
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
			case sf::Event::Closed://al cerrar la ventana guardo los high scores separandolos con un -
				filo.open("test.txt");
				filo << to_string(highscores[0]) + "-" + to_string(highscores[1]) + "-" + to_string(highscores[2]) + "-";
				filo.close();
				window.close();
				break;
			}

		}
}


void game::update(sf::Time dela)
{
	
	/*-if (dispara && jugador.poder ) {
		d = true;
	}*/
	tiempo += dela.asSeconds();
	tdisparo += dela.asSeconds();
	tmanzana += dela.asSeconds();
	if (tdisparo > .1f) {
		tdisparo = 0;
		for (list<fuego*>::iterator a = disparos.begin(); a != disparos.end(); a++) {
			(*a)->update();
		}
		if(disparos.size() != 0 && (*disparos.rbegin())->no == true) {
			delete *disparos.rbegin();
			disparos.pop_back();
		}
	}
	if (tiempo > float(1.f/float(velocidad))) {//la serpiente se movera un cuadro del grid dependiendo de la velocidad
		//el lugador no puede voltearse 180 grados por lo que antes revisara si no lo esta haciendo
		if (up  && jugador.direccion != 3) {
			jugador.direccion = 1;
		}
		else if (down && jugador.direccion != 1) {
			jugador.direccion = 3;
		}
		else if (right  && jugador.direccion != 4) {
			jugador.direccion = 2;
		}
		else if (left && jugador.direccion != 2) {
			jugador.direccion = 4;
		}
		tiempo = 0;
		if (jugador.cabeza.getPosition() == activ1.poder.getPosition()) {
			//jugador.poder = true;
			activ1.ya = false;
		}
		if (jugador.perdiste == false) {//si el jugador no a perdido se actualizara
			jugador.update(grid.size());
			activ1.update(&jugador);
		}
		for (int a = 0; a < enemys.size(); a++) {
			enemys[a].updates();
			/*if (enemi.perdiste == false) {
				
			}*/
		}
		
	}
	if (tmanzana > 13) {
		for (int a = 0; a < enemys.size(); a++) {
			enemys[a].tamaño += 1;
		}
		
		tmanzana = 0;
		//random(manzana, &grid, -1);*/
	}
	for (int a = 0; a < manzanas.size(); a++) {
		if (manzanas[a].getPosition() == jugador.cabeza.getPosition()) {//si el jugador se encuentra con una manzana 
			tmanzana = 0;
			puntos += 1;//se aumenta la puntuacion
			puntacion.setString(to_string(puntos));//se actualiza la puntuacion
			random(manzana, &grid, a);//se genera una manzana en un lugar random
			jugador.tamaño += 1;//el jugador crece
		}
	}
	
	if (d == true) {
		d = false;
		disparos.push_front(new fuego());
		(*disparos.begin())->bola.setPosition(jugador.cabeza.getPosition());
		(*disparos.begin())->direccion = jugador.direccion;
	}
}
void game::random(rectangulo a, vector<vector<int>>* gird, int e)
{//se generaran posisiones dentro de la grid a lo random hasta que quede en un lugar vacio
	int x = (rand() % 30);
	int y = (rand() % 30);
	while ((*gird)[x][y] == 3|| (*gird)[x][y] == 1) {
		x = (rand() % 30);
		y = (rand() % 30);
	}
	if (e == -1) {
		manzanas.push_back(a);
		manzanas[manzanas.size() - 1].setPosition((x + 1) * 20 - 10, (y + 1) * 20 - 10);
	}
	else {
		manzanas[e].setPosition((x + 1) * 20 - 10, (y + 1) * 20 - 10);
	}
}
/*void game::renderpause()
{
	
	nada.setFillColor(sf::Color(200, 200, 200, 100));
	
	nada.setSize({ 600,600 });

	nada.setPosition(0, 0);
	if (!ya) {
		window.draw(nada);
	}
	ya = true;
	/*for (int a = 0; a < 3; a++) {
		window.draw(tmenu[a]);
	}
	window.display();
}*/

void game::render()// se dibuja todo
{	
	window.clear();
	fcamera(ncamera);
	window.setView(camera);
	//para las paredes primero se dibuja abajo los ladrillos y luego al dibujar el piso see deja espacio donde hay pared
	for (int a = 0; a < grid.size(); a++) {
		for (int e = 0; e < grid.size(); e++) {
			fondo.setPosition(a * 60, e * 60);
			window.draw(fondo);
		}
	}
	for (int a = 0; a < 30; a++) {
		for (int e = 0; e < 30; e++) {
			if (grid[a][e] == 3) {
			}
			else {
				piso.setPosition(a * 20, e * 20);
				window.draw(piso);
			}
		}
	}
	//perder->dibujar(&window);
	/*for (int a = 0; a < paredes.size(); a++) {
		paredes[a].dibujar(&window);
	}*/
	//activ1.dibujar(&window);

	for (rectangulo a : manzanas) {
		window.draw(a);
	}
	for (fuego* a : disparos) {
		(*a).dibujar(&window);
	}
	/*window.draw(enemi.cabeza);
	for (rectangulo* a : enemi.cuerpo) {
		window.draw(*a);
	}
	window.draw(enemi.cola);*/
	for (enemy a : enemys) {
		a.dibujar(&window);

	}
	jugador.dibujar(&window);
	if (jugador.perdiste == true) {
		window.draw(geimover);
	}
	window.draw(uidraw(puntacion,&camera));
	camera.setCenter(jugador.cabeza.getPosition());
	if (camera.getCenter().x < 300) {
		camera.setCenter(300,camera.getCenter().y);
	}
	if (camera.getCenter().y < 300) {
		camera.setCenter( camera.getCenter().x,300 );
	}
	if (camera.getCenter().x > grid.size()*20-320) {
		camera.setCenter(grid.size() * 20 - 320, camera.getCenter().y);
	}
	if (camera.getCenter().y > grid.size() * 20 - 320) {
		camera.setCenter(camera.getCenter().x,grid.size() * 20 - 320 );
	}
	fondo.setPosition(0, 0);
	window.display();
}


