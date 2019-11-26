#include "pch.h"
#include "rectangulo.h"

rectangulo::rectangulo()
{//todos los rectangulos tienen el mismo tamaño y origen para que esten de acuerdo con el grid
	setSize(sf::Vector2<float>(20, 20));
	setOrigin(10, 10);
	
}
void rectangulo::textura(std::string textrue)
{
	e.loadFromFile(textrue);
	setTexture(&e);
}
rectangulo::~rectangulo()
{
}
