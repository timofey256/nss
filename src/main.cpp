#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Grid.hpp"

constexpr char APPLICATION_TITLE[] = "Natural Selection Simulation";
constexpr int WINDOW_WIDTH = 1400;
constexpr int WINDOW_HEIGHT = 700;

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
			grid.moveCells();	
			window.display();
		}
	}

	return 0;
}
