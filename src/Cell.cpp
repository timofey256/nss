#include <iostream>
#include "Cell.hpp"

Cell::Cell() : Cell(0,0,0) {}

Cell::Cell(int e) : Cell(e, 3.f, 3.f) {}

std::array<Gene, GENOME_LENGTH> Cell::generateRandomGenome() {
    std::array<Gene, GENOME_LENGTH> genome;
    for (int i=0; i<GENOME_LENGTH; i++) {
        Gene new_gene = {rand() % (LAYERS_NUM-1),
            rand() % NEURONS_NUM,
            rand() % NEURONS_NUM,
            rand() % MAX_WEIGHT };
            genome[i] = new_gene;
    }

    return genome;
}

Cell::Cell(int e, float size, float sense) {
	energy = e;
	r_size = size;
	r_sense = sense;
	genome = generateRandomGenome(); 
	
	brain = NeuralNetwork(genome);
}

Cell::Cell(int e, float size, float sense, std::array<Gene, GENOME_LENGTH> g) {
	energy = e;
	r_size = size;
	r_sense = sense;
	genome = g;
	brain = NeuralNetwork(genome);
}

Cell::~Cell() {}

bool Cell::isNullCell() {
	if (r_size == 0.f) {
		return true;
	}

	return false;
}
