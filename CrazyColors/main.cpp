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

	Grid grid({
		Hexagon("RGB", &Conversions::fromRGB),
		Hexagon("CMY", &Conversions::fromCMY),
		Hexagon("HSL", &Conversions::fromHSL),
		Hexagon("HSV", &Conversions::fromHSV)
		}, 10.f, 10.f);

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