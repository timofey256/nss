#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

constexpr char APPLICATION_TITLE[] = "Natural Selection Simulation";
constexpr int WINDOW_WIDTH = 1400;
constexpr int WINDOW_HEIGHT = 700;

constexpr float GRID_OFFSET = 50.f;
constexpr float GRID_PIXEL_SIZE = 512.f;
constexpr int GRID_CELLS_SIZE = 128;

constexpr int CELLS_MAX_AMOUNT = 100;
constexpr int FOOD_MAX_AMOUNT = 20;

class Cell {
public:
	Cell() : Cell(0,0,0)
	{}

	Cell(int e, int size = 3.f, int sense = 3.f) {
		energy = e;
		r_size = size;
		r_sense = sense;
	}

	sf::CircleShape getShape() {
		sf::CircleShape circle(r_size);	
		circle.setFillColor(sf::Color::Red);

		return circle;
	}

	bool isNullCell() {
		if (r_size == 0.f) {
			return true;
		}

		return false;
	}
private:
	int energy;
	float r_size; // size radius
	float r_sense; // sense radius
};

class Food {
public:
	int energy;

	Food() : Food(0)
	{}	

	Food(int en) {
		energy = en;	
	}

	sf::CircleShape getShape() {
		sf::CircleShape circle(2.f);	
		circle.setFillColor(sf::Color::Green);

		return circle;
	}

	bool isNullCell() {
		if (energy == 0) {
			return true;
		}	

		return false;
	}
};

class Grid {
public:
	Grid() {
		grid = getGridShape();	
		populate();
		growFood();
	}

	void draw(sf::RenderWindow *window) {
		window->draw(grid);	
		drawCells(window);
		drawFood(window);
	}

private:
	Cell cells[GRID_CELLS_SIZE][GRID_CELLS_SIZE];
	Food food[GRID_CELLS_SIZE][GRID_CELLS_SIZE];
	sf::RectangleShape grid;

	sf::RectangleShape getGridShape() {
		sf::RectangleShape grid(sf::Vector2f(GRID_PIXEL_SIZE, GRID_PIXEL_SIZE));	
		grid.setPosition(GRID_OFFSET, GRID_OFFSET);
		grid.setFillColor(sf::Color::Black);
		grid.setOutlineThickness(2.f);
		grid.setOutlineColor(sf::Color::White);

		return grid;
	}

	void populate() {
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

	void growFood() {
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
	
	void drawFood(sf::RenderWindow *window) {
		for (int i=0; i<GRID_CELLS_SIZE; i++) {
			for (int j=0; j<GRID_CELLS_SIZE; j++) {
				if (!food[i][j].isNullCell()) {
					Food f = food[i][j];
					sf::CircleShape cs = f.getShape();
					
					cs.setPosition(GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*i,
						       GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*j);
					window->draw(cs);	
				}
			}				
		}
	}

	void drawCells(sf::RenderWindow *window) {
		for (int i=0; i<GRID_CELLS_SIZE; i++) {
			for (int j=0; j<GRID_CELLS_SIZE; j++) {
				if (!cells[i][j].isNullCell()) {
					Cell cell = cells[i][j];
					sf::CircleShape cs = cell.getShape();
					
					cs.setPosition(GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*i,
						       GRID_OFFSET + GRID_PIXEL_SIZE/GRID_CELLS_SIZE*j);
					window->draw(cs);	
				}
			}				
		}
	}
};


int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), APPLICATION_TITLE);

	Grid grid;	
	while (window.isOpen()) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}

			window.clear(sf::Color::Black);
			grid.draw(&window);	
			window.display();
		}
	}

	return 0;
}
