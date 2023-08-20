class Cell {
public:
        Cell();
        Cell(int e, float size, float sense);
        Cell(int e);
        bool isNullCell();

        int energy;
        float r_size; 
	float r_sense;
};

