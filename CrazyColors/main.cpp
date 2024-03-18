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

	Hexagon rgb("RGB", [](auto v) { return Conversions::fromRGB(v); });

	Hexagon cmy("CMY", [](auto v) { return Conversions::fromCMY(v); });

	Hexagon hsl("HSL", [](auto v) { return Conversions::fromHSL(v); });

	Hexagon hsv("HSV", [](auto v) { return Conversions::fromHSV(v); });

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