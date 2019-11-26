#include "pch.h"
#include "fuego.h"


fuego::fuego()
{
	bola.textura("boladefuego.png");
	incendio.textura("fuego.png");
}

void fuego::dibujar(sf::RenderWindow* window)
{
	if (no == false) {
		if (ya == false) {
			window->draw(bola);
		}
		else {
			window->draw(incendio);

		}
	}
}


void fuego::update()
{
	if (paso < 10) {
		switch (direccion) {
			
		case 3:
			bola.setPosition(bola.getPosition().x, ((int)bola.getPosition().y + 20) % 600);
			break;
		case 2:
			bola.setPosition(((int)bola.getPosition().x + 20) % 600, bola.getPosition().y);
			break;
		case 4:
			bola.setPosition(((int)bola.getPosition().x + 580) % 600, bola.getPosition().y);
			break;
		default:
			bola.setPosition(bola.getPosition().x, ((int)bola.getPosition().y + 580) % 600);
		}
	}
	else if (paso == 10) {
		ya = true;
		incendio.setPosition(bola.getPosition().x, bola.getPosition().y);
	}
	else if(paso ==19){
		no = true;
	}
	paso += 1;
}

fuego::~fuego()
{
}
