#include <SFML/Graphics.hpp>

int main(void) {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Crazy Colors", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

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