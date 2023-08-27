#include "Cell.hpp"
#include "Nature.hpp"

Cell::Cell() : Cell(0,0,0)
{}

Cell::Cell(int e) : Cell(e, 3.f, 3.f)
{}

Cell::Cell(int e, float size, float sense) {
	energy = e;
	r_size = size;
	r_sense = sense;
	genome = Nature::generateRandomGenome(GENOM_LENGTH);
}

Cell::Cell(int e, float size, float sense, std::vector<Gene> g) {
	energy = e;
	r_size = size;
	r_sense = sense;
	genome = g;	
}

bool Cell::isNullCell() {
	if (r_size == 0.f) {
		return true;
	}

	return false;
}
