#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
using namespace std;
class pared
{
public:
	pared();
	void setposition(int,int), dibujar(sf::RenderWindow*),poner(vector<vector<int>>*, vector<vector<int>> patron);
	sf::RectangleShape nada;
	~pared();
private:
	vector<vector<int>> ptrn;
	int x, y;
};

