#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;
class selector
{
private:
	
public:
	vector<sf::Text> textos;
	sf::Font letras;
	sf::Text texto;
	selector();
	int cual;
	int x, y,z = 0;
	void render(sf::RenderWindow*,sf::View*,sf::Text(uidraw)(sf::Text, sf::View*),bool,bool,bool), lista(vector<string>);
	~selector();
};

