#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"

constexpr float GRID_OFFSET = 50.f;
constexpr float GRID_PIXEL_SIZE = 512.f;

constexpr int CELLS_MAX_AMOUNT = 100;
constexpr int FOOD_MAX_AMOUNT = 20;

Grid::Grid() {
	for (int i = 0; i < GRID_CELLS_SIZE; i++) {
        for (int j = 0; j < GRID_CELLS_SIZE; j++) {
            cells[i][j] = nullptr;
            food[i][j] = nullptr;
        }
    }
	
	grid = getGridShape();
	populate();
	growFood();
}

void Grid::draw(sf::RenderWindow *window) {
	window->draw(grid);
	drawCells(window);
	drawFood(window);
}

// TODO: decompose code!
void Grid::moveCells() {
	for (int x=0; x<GRID_CELLS_SIZE; x++) {
		for (int y=0; y<GRID_CELLS_SIZE; y++) {
			if (cells[x][y] != nullptr) {
				std::vector<double> input = {
					static_cast<double>(x), 
					static_cast<double>(y), 
					cells[x][y]->energy,
					cells[x][y]->r_size,
					0,
					0
				};

				cells[x][y]->brain.feedForward(&input);

				std::vector<double> output;
				cells[x][y]->brain.getResults(&output);
				
				double xDelta = (cells[x][y]->NORMAL_SPEED-cells[x][y]->r_size)*output[0];
				double yDelta = (cells[x][y]->NORMAL_SPEED-cells[x][y]->r_size)*output[1];

				int newX = (int)(x + xDelta);
				int newY = (int)(y + yDelta);

				if (newX >= GRID_CELLS_SIZE) {
					newX = GRID_CELLS_SIZE-1;
				}
				else if (newX < 0) {
					newX = 0;
				}

				if (newY >= GRID_CELLS_SIZE) {
					newY = GRID_CELLS_SIZE-1;
				}
				else if (newY < 0) {
					newY = 0;
				}

				if (newX != x || newY != y) {
					Cell* new_cell = new Cell(cells[x][y]->energy, cells[x][y]->r_size, cells[x][y]->r_sense, cells[x][y]->genome);
					cells[newX][newY] = new_cell;
	
					delete cells[x][y];
					cells[x][y] = nullptr;
				}

				cells[newX][newY]->energy -= cells[newX][newY]->r_size*5;

				if (food[newX][newY] != nullptr) {
					std::cout << "eaten" << std::endl;
					cells[newX][newY]->energy += food[newX][newY]->energy;
					delete food[newX][newY];
					food[newX][newY] = nullptr;
				}

				if (cells[newX][newY]->energy <= 0) {
					delete cells[newX][newY];
					cells[newX][newY] = nullptr;
				}
			} 
		}	
	}
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
		
		if (cells[pos_x][pos_y] == nullptr) {
			Cell* new_cell = new Cell(100);
			cells[pos_x][pos_y] = new_cell;
			n++;
		}
	}
}

void Grid::growFood() {
	srand(time(0));

	for (int i=0; i<GRID_CELLS_SIZE; i++) {
		for (int j=0; j<GRID_CELLS_SIZE; j++) {
			if (food[i][j] != nullptr) {
				std::cout << "(2) non null before init: " << food[i][j] << std::endl;
			}
		}
	}

	int n = 0;
	while (n < FOOD_MAX_AMOUNT) {
		int pos_x = rand() % GRID_CELLS_SIZE;
		int pos_y = rand() % GRID_CELLS_SIZE;
		if (food[pos_x][pos_y] == nullptr && cells[pos_x][pos_y] == nullptr) {
			Food* new_food = new Food(25);
			food[pos_x][pos_y] = new_food;
			n++;
		}
	}
}

void Grid::drawFood(sf::RenderWindow *window) {
	for (int i=0; i<GRID_CELLS_SIZE; i++) {
		for (int j=0; j<GRID_CELLS_SIZE; j++) {
			if (food[i][j] != nullptr) {
				sf::CircleShape cs(3.f);
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
			if (cells[i][j] != nullptr) {
				Cell* cell = cells[i][j];
				sf::CircleShape cs(cell->r_size);
				cs.setFillColor(sf::Color::Red);

				cs.setPosition(GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*i,
					       GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*j);
				window->draw(cs);
			}
		}
	}
}
