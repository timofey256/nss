#include <SFML/Graphics.hpp>
#include "Grid.hpp"

constexpr float GRID_OFFSET = 50.f;
constexpr float GRID_PIXEL_SIZE = 512.f;

constexpr int CELLS_MAX_AMOUNT = 100;
constexpr int FOOD_MAX_AMOUNT = 20;

Grid::Grid() {
	grid = getGridShape();
	populate();
	growFood();
}

void Grid::draw(sf::RenderWindow *window) {
	window->draw(grid);
	drawCells(window);
	drawFood(window);
}

sf::RectangleShape Grid::getGridShape() {
	sf::RectangleShape grid(sf::Vector2f(GRID_PIXEL_SIZE, GRID_PIXEL_SIZE));
	grid.setPosition(GRID_OFFSET, GRID_OFFSET);
	grid.setFillColor(sf::Color::Black);
	grid.setOutlineThickness(2.f);
	grid.setOutlineColor(sf::Color::White);

	return grid;
}

void Grid::populate() {
	srand(time(0));

	int n = 0;
	while (n < CELLS_MAX_AMOUNT) {
		int pos_x = rand() % GRID_CELLS_SIZE;
		int pos_y = rand() % GRID_CELLS_SIZE;

		if (cells[pos_x][pos_y].isNullCell()) {
			Cell new_cell(100);
			cells[pos_x][pos_y] = new_cell;
			n++;
		}
	}
}

void Grid::growFood() {
	srand(time(0));

	int n = 0;
	while (n < FOOD_MAX_AMOUNT) {
		int pos_x = rand() % GRID_CELLS_SIZE;
		int pos_y = rand() % GRID_CELLS_SIZE;

		if (food[pos_x][pos_y].isNullCell() && cells[pos_x][pos_y].isNullCell()) {
			Food new_food(100);
			food[pos_x][pos_y] = new_food;
			n++;
		}
	}
}

void Grid::drawFood(sf::RenderWindow *window) {
	for (int i=0; i<GRID_CELLS_SIZE; i++) {
		for (int j=0; j<GRID_CELLS_SIZE; j++) {
			if (!food[i][j].isNullCell()) {
				Food f = food[i][j];
				sf::CircleShape cs(2.f);
				cs.setFillColor(sf::Color::Green);

				cs.setPosition(GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*i,
					       GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*j);
				window->draw(cs);
			}
		}
	}
}

void Grid::drawCells(sf::RenderWindow *window) {
	for (int i=0; i<GRID_CELLS_SIZE; i++) {
		for (int j=0; j<GRID_CELLS_SIZE; j++) {
			if (!cells[i][j].isNullCell()) {
				Cell cell = cells[i][j];
				sf::CircleShape cs(cell.r_size);
				cs.setFillColor(sf::Color::Red);


				cs.setPosition(GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*i,
					       GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*j);
				window->draw(cs);
			}
		}
	}
}
