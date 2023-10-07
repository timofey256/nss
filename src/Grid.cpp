#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"

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

				int newX = validateCoordinate((int)(x + xDelta));
				int newY = validateCoordinate((int)(y + yDelta));

				if (newX != x || newY != y) {
					Cell* new_cell = new Cell(cells[x][y]->energy, cells[x][y]->r_size, cells[x][y]->r_sense, cells[x][y]->genome);
					cells[newX][newY] = new_cell;
					cells[x][y] = nullptr;
				}

				cells[newX][newY]->energy -= cells[newX][newY]->r_size*ENERGY_CONSUMPTION_MULTIPLIER;
				if (cells[newX][newY] != nullptr) {
					eatFood(newX, newY);		
				}
		
				if (cells[newX][newY]->energy <= 0) {
					cells[newX][newY] = nullptr;
					this->current_cell_amount--;
				}
			} 
		}	
	}
}

void Grid::repopulate() {
	int children_per_parent = CELLS_MAX_AMOUNT / this->current_cell_amount;
	int new_amount = 0;
	for (int i=0; i<GRID_CELLS_SIZE; i++) {
		for (int j=0; j<GRID_CELLS_SIZE; j++) {
			if (cells[i][j] != nullptr ) {
				Cell* mutated = mutate_cell(cells[i][j]);
				for (int i=0; i<3; i++) {
					set_cell_to_rand_pos(mutated);
					new_amount++;
				}
				cells[i][j] = nullptr;
			}
		}
	}

	current_cell_amount = new_amount;
	growFood();
}

void Grid::set_cell_to_rand_pos(Cell* cell) {
	srand(time(0));
	bool is_set = false;
	while (!is_set) {
		int pos_x = rand() % GRID_CELLS_SIZE;
		int pos_y = rand() % GRID_CELLS_SIZE;
		if (cells[pos_x][pos_y] == nullptr) {
			cells[pos_x][pos_y] = cell;
			is_set = true;
		}
	}
}

Cell* Grid::mutate_cell(Cell* cell) {
    Cell* mutated_cell = new Cell();
    mutated_cell->energy = 100;
    mutated_cell->r_size = cell->r_size;
    mutated_cell->r_sense = cell->r_sense;
    mutated_cell->genome = cell->genome; // TO BE MUTATED!
    return mutated_cell;
}

int Grid::validateCoordinate(int coord) {
	if (coord >= GRID_CELLS_SIZE) {
		coord = GRID_CELLS_SIZE-1;
	}
	else if (coord < 0) {
		coord = 0;
	}

	return coord;
}

void Grid::eatFood(int x, int y) {
	if (food[x][y] != nullptr) {
		cells[x][y]->energy += food[x][y]->energy;
		delete food[x][y];
		food[x][y] = nullptr;
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
				food[i][j] = nullptr;
			}
		}
	}

	int n = 0;
	while (n < FOOD_MAX_AMOUNT) {
		int pos_x = rand() % GRID_CELLS_SIZE;
		int pos_y = rand() % GRID_CELLS_SIZE;
		if (food[pos_x][pos_y] == nullptr && cells[pos_x][pos_y] == nullptr) {
			Food* new_food = new Food(FOOD_SUPPLY);
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
