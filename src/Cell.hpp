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
	
        Cell& operator=(const Cell& other) {
                energy = other.energy;
                r_sense = other.r_sense;
                r_size = other.r_size;
                genome = other.genome;
                return *this;
        }
        
        ~Cell();

        int energy;
        float r_size; 
	float r_sense;
	NeuralNetwork brain;
	std::array<Gene, GENOME_LENGTH> genome;

        const static int NORMAL_SPEED = 10;
        
private:
        std::array<Gene, GENOME_LENGTH> generateRandomGenome();
};

#endif CELL_H