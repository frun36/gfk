#include <SFML/Graphics.hpp>

#include "Sokoban.hpp"

int main(void) {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Sokoban", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	Sokoban sokoban("map.txt");

	sokoban.setScale(window.getSize());

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
				sokoban.setScale(sf::Vector2u(event.size.width, event.size.height));
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Down:
					sokoban.movePlayer(Direction::DOWN);
					break;
				case sf::Keyboard::Right:
					sokoban.movePlayer(Direction::RIGHT);
					break;
				case sf::Keyboard::Up:
					sokoban.movePlayer(Direction::UP);
					break;
				case sf::Keyboard::Left:
					sokoban.movePlayer(Direction::LEFT);
					break;
				}
				
				break;
			}
		}

		window.clear();
		window.draw(sokoban);
		window.display();
	}

	return 0;
}