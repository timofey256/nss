#include <array>
#include "Nature.hpp"

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
	std::array<Gene, GENOME_LENGTH> genome;
};

