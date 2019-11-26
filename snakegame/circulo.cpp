#include "pch.h"
#include "circulo.h"

circulo::circulo()
{
	setRadius(10);
	setOrigin(10, 10);
}
void circulo::textura(std::string textrue)
{
	e.loadFromFile(textrue);
	setTexture(&e);
}
circulo::~circulo()
{
}
