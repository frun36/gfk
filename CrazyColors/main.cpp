#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"

sf::Font font;

int main(void) {
	if (!font.loadFromFile("consola.ttf")) {
		std::cerr << "Couldn't load font\n";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Crazy Colors", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	Hexagon hex(sf::Vector2f(100, 100), sf::Vector2f(800, 800), "RGB", [](std::optional<sf::Vector3f> v) {
		if (v.has_value()) {
			return sf::Color(255 * v.value().x, 255 * v.value().y, 255 * v.value().z);
		}
		else {
			return sf::Color::Transparent;
		}
		});

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