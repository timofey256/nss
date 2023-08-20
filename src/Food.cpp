#include <SFML/Graphics.hpp>
#include "Food.hpp"

Food::Food() : Food::Food(0)
{ }

Food::Food(int en) {
	energy = en;
}

sf::CircleShape Food::getShape() {
	sf::CircleShape circle(2.f);
	circle.setFillColor(sf::Color::Green);

	return circle;
}

bool Food::isNullCell() {
	if (energy == 0) {
		return true;
	}

	return false;
}
