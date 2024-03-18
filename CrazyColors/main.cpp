#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"
#include "Grid.hpp"

sf::Font font;

int main(void) {
	if (!font.loadFromFile("consola.ttf")) {
		std::cerr << "Couldn't load font\n";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Crazy Colors", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	Hexagon rgb("RGB", [](std::optional<sf::Vector3f> v) {
		if (v.has_value()) {
			return sf::Color(255 * v.value().x, 255 * v.value().y, 255 * v.value().z);
		}
		else {
			return sf::Color::Transparent;
		}
		});

	Hexagon cmy("CMY", [](std::optional<sf::Vector3f> v) {
		return v.has_value() ? sf::Color(255 - 255 * v.value().x, 255 - 255 * v.value().y, 255 - 255 * v.value().z) : sf::Color::Transparent;
		});

	Hexagon hsl("HSL", [](std::optional<sf::Vector3f> v) {
		return v.has_value() ? sf::Color(255 * v.value().x, 255 * v.value().y, 255 * v.value().z) : sf::Color::Transparent;
		});

	Hexagon hsv("HSV", [](std::optional<sf::Vector3f> v) {
		if (v.has_value()) {
			return sf::Color(255 * v.value().x, 255 * v.value().y, 255 * v.value().z);
		}
		else {
			return sf::Color::Transparent;
		}
		});

	Grid grid({ rgb, cmy, hsl, hsv }, 10.f, 10.f);

	grid.resize(window.getSize().x, window.getSize().y);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(
					0,
					0,
					static_cast<float>(event.size.width),
					static_cast<float>(event.size.height)
				)));
				grid.resize(event.size.width, event.size.height);
				break;
			}
		}

		window.clear(sf::Color(32, 32, 32));
		window.draw(grid);
		window.display();
	}

	return 0;
}