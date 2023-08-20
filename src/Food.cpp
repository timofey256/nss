#include <SFML/Graphics.hpp>
#include "Food.hpp"

Food::Food() : Food::Food(0)
{ }

Food::Food(int en) {
	energy = en;
}

bool Food::isNullCell() {
	if (energy == 0) {
		return true;
	}

	return false;
}
