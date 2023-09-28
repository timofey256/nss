#include "Cell.hpp"
#include "Food.hpp"

constexpr int GRID_CELLS_SIZE = 64; 
constexpr int ENERGY_CONSUMPTION_MULTIPLIER = 5; 

class Grid {
public:
        Grid();
        void draw(sf::RenderWindow *window);
        void moveCells();

private:
        Cell* cells[GRID_CELLS_SIZE][GRID_CELLS_SIZE];
        Food* food[GRID_CELLS_SIZE][GRID_CELLS_SIZE];
        sf::RectangleShape grid;
        sf::RectangleShape getGridShape();
        void populate();
        void growFood();
        void drawFood(sf::RenderWindow *window);
        void drawCells(sf::RenderWindow *window);

	int validateCoordinate(int c);
	void checkDeadCell(Cell* c);
	void eatFood(int x, int y);
};
