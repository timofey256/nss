#include "Gene.cpp"
#include <vector>

constexpr int GENOM_LENGTH = 20;

class Cell {
public:
        Cell();
        Cell(int e);
        Cell(int e, float size, float sense);
	Cell(int e, float size, float sense, std::vector<Gene> g);
        bool isNullCell();

        int energy;
        float r_size; 
	float r_sense;
	std::vector<Gene> genome;
};

