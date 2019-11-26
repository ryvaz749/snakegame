#pragma once
#include "SFML/Graphics.hpp"
class circulo :
	public sf::CircleShape
{
public:
	sf::Texture e;
	void textura(std::string textrue);
	circulo();
	~circulo();
};

