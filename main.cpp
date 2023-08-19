#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

constexpr char APPLICATION_TITLE[] = "Natural Selection Simulation";
constexpr int WINDOW_WIDTH = 1400;
constexpr int WINDOW_HEIGHT = 700;

constexpr float GRID_OFFSET = 50.f;
constexpr float GRID_PIXEL_SIZE = 512.f;
constexpr int GRID_CELLS_SIZE = 128;
constexpr int CELLS_MAX_SIZE = 100;

class Cell {
public:
	Cell() : Cell(0,0,0)
	{}

	Cell(int e, int size = 3.f, int sense = 3.f) {
		energy = e;
		r_size = size;
		r_sense = sense;
	}

	sf::CircleShape getCircleShape() {
		sf::CircleShape circle(r_size);	
		circle.setFillColor(sf::Color(125, 255, 5));

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

class Grid {
public:
	Grid() {
		grid = getGridShape();	
		populate();
	}

	void draw(sf::RenderWindow *window) {
		window->draw(grid);	
		drawCells(window);
	}

private:
	Cell cells[GRID_CELLS_SIZE][GRID_CELLS_SIZE];
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
		while (n < CELLS_MAX_SIZE) {
			int pos_x = rand() % GRID_CELLS_SIZE;
			int pos_y = rand() % GRID_CELLS_SIZE;

			if (cells[pos_x][pos_y].isNullCell()) {
				Cell new_cell(100);
				cells[pos_x][pos_y] = new_cell;
				n++;
			}
		}
	}

	void drawCells(sf::RenderWindow *window) {
		for (int i=0; i<GRID_CELLS_SIZE; i++) {
			for (int j=0; j<GRID_CELLS_SIZE; j++) {
				if (!cells[i][j].isNullCell()) {
					Cell cell = cells[i][j];
					sf::CircleShape cs = cell.getCircleShape();
					
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
