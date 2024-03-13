#include <SFML/Graphics.hpp>

#include "Sokoban.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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
					sokoban.movePlayer(Sokoban::Direction::DOWN);
					break;
				case sf::Keyboard::Right:
					sokoban.movePlayer(Sokoban::Direction::RIGHT);
					break;
				case sf::Keyboard::Up:
					sokoban.movePlayer(Sokoban::Direction::UP);
					break;
				case sf::Keyboard::Left:
					sokoban.movePlayer(Sokoban::Direction::LEFT);
					break;
				}
				break;
			}
		}

		if (sokoban.isModified()) {
			window.clear();
			window.draw(sokoban);
			sokoban.markUnmodified();
			window.display();
		}
		

		if (sokoban.checkWin()) {
			MessageBoxA(NULL, "You completed the game!", "You won!", MB_OK);
			return 0;
		}
	}

	return 0;
}