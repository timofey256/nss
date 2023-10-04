#include "Cell.hpp"
#include "Food.hpp"

constexpr float GRID_OFFSET = 50.f;
constexpr float GRID_PIXEL_SIZE = 512.f;

constexpr int CELLS_MAX_AMOUNT = 100;
constexpr int FOOD_MAX_AMOUNT = 50;
constexpr int FOOD_SUPPLY = 30;
constexpr int GRID_CELLS_SIZE = 64; 
constexpr int ENERGY_CONSUMPTION_MULTIPLIER = 5; 

class Grid {
public:
        int current_cell_amount = CELLS_MAX_AMOUNT;

        Grid();
        void draw(sf::RenderWindow *window);
        void moveCells();
        void repopulate();

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

        void set_cell_to_rand_pos(Cell* c);
        Cell* mutate_cell(Cell* c);
};
