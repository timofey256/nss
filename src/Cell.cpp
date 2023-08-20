#include "Cell.hpp"

Cell::Cell() : Cell(0,0,0)
{}

Cell::Cell(int e) : Cell(e, 3.f, 3.f)
{}

Cell::Cell(int e, float size, float sense) {
	energy = e;
	r_size = size;
	r_sense = sense;
}

bool Cell::isNullCell() {
	if (r_size == 0.f) {
		return true;
	}

	return false;
}
