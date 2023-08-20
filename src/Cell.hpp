class Cell {
public:
        Cell();
        Cell(int e, int size, int sense);
        sf::CircleShape getShape();
        bool isNullCell();
private:
        int energy;
        float r_size; 
	float r_sense;
};

