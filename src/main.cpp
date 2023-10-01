#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>    
#include <SFML/Graphics.hpp>
#include "Grid.hpp"

constexpr char APPLICATION_TITLE[] = "Natural Selection Simulation";
constexpr int WINDOW_WIDTH = 1400;
constexpr int WINDOW_HEIGHT = 700;
constexpr int STEP_IN_MILLIS = 1000;
constexpr int NEW_GENERATION_THRESHOLD = 20;

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), APPLICATION_TITLE);
	
	auto now = std::chrono::system_clock::now().time_since_epoch();
	auto last_in_millis = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();

	Grid grid;
	while (window.isOpen()) {
		if (grid.current_cell_amount == 0) {
			std::cout << "All cells died. Start again" << std::endl; 
			break;
		}
		else if (grid.current_cell_amount <= NEW_GENERATION_THRESHOLD) {
			grid.repopulate();
		}

		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		grid.draw(&window);

		auto n = std::chrono::system_clock::now().time_since_epoch();
		auto cur = std::chrono::duration_cast<std::chrono::milliseconds>(n).count();
		
		if (cur-last_in_millis > STEP_IN_MILLIS) {
			grid.moveCells();
			last_in_millis = cur;	
		}
		window.display();
	}

	return 0;
}
