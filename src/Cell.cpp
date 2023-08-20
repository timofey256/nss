#include <SMFL/Graphics.hpp>
#include "Cell.hpp"

Cell::Cell() : Cell(0,0,0)
{}

Cell::Cell(int e, int size = 3.f, int sense = 3.f) {
	energy = e;
	r_size = size;
	r_sense = sense;
}

sf::CircleShape Cell::getShape() {
	sf::CircleShape circle(r_size);
	circle.setFillColor(sf::Color::Red);

	return circle;
}

bool Cell::isNullCell() {
	if (r_size == 0.f) {
		return true;
	}

	return false;
}
