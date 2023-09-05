#ifndef CELL_H
#define CELL_H

#include <array>
#include <cstddef>

#include "NeuralNetwork.hpp"

class Cell {
public:
        Cell();
        Cell(int e);
        Cell(int e, float size, float sense);
	Cell(int e, float size, float sense, std::array<Gene, GENOME_LENGTH>);
        bool isNullCell();
	~Cell();

        int energy;
        float r_size; 
	float r_sense;
	NeuralNetwork brain;
	std::array<Gene, GENOME_LENGTH> genome;

private:
        std::array<Gene, GENOME_LENGTH> generateRandomGenome();
};

#endif CELL_H