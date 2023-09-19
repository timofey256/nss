#include <iostream>
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

void Grid::moveCells() {
	for (int x=0; x<GRID_CELLS_SIZE; x++) {
		for (int y=0; y<GRID_CELLS_SIZE; y++) {
			if (cells[x][y].energy != 0) {  // there's an organism in this cell
				std::vector<double> input = {
											static_cast<double>(x), 
											static_cast<double>(y), 
											cells[x][y].energy,
											0,
											0,
											cells[x][y].r_size};

				cells[x][y].brain.feedForward(&input);

				std::vector<double> output;
				cells[x][y].brain.getResults(&output);
				
				double xDelta = (cells[x][y].NORMAL_SPEED-cells[x][y].r_size)*output[0];
				double yDelta = (cells[x][y].NORMAL_SPEED-cells[x][y].r_size)*output[1];
				

				int newX = (int)(x + xDelta);
				int newY = (int)(y + yDelta);

				if (newX != x || newY != y) {
					if (newX < GRID_CELLS_SIZE && newX >= 0 && newY < GRID_CELLS_SIZE && newY >= 0) {
						cells[newX][newY] = cells[x][y];
					}
					cells[x][y] = Cell();
				}
				//std::cout << "Input : " << input[0] << " " << input[1] << " " << input[2] << std::endl; 
				// std::cout << "\t" << "xDelta: " << xDelta << ". yDelta: " << yDelta << std::endl; 
				// std::cout << "Output neuron weights : " << output[0] << " " << output[1] << std::endl; 
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
		
		if (cells[pos_x][pos_y].isNullCell()) {
			Cell new_cell(50);
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
