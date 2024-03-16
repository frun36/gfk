#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"

int main(void) {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Crazy Colors", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	

	RGB hex(sf::Vector2f(100, 100), sf::Vector2f(800, 800));

	window.draw(hex);
	window.display();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}

	return 0;
}