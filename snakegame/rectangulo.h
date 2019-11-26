#pragma once
#include "SFML/Graphics.hpp"
class rectangulo :
	public sf::RectangleShape
{
public:
	sf::Texture e;
	void textura(std::string textrue);
	rectangulo();
	~rectangulo();
};

