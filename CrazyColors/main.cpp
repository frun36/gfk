#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"
#include "Grid.hpp"
#include "Slider.hpp"
#include <vector>
#include <numeric>

sf::Font font;

int main(void) {
	if (!font.loadFromFile("consola.ttf")) {
		std::cerr << "Couldn't load font\n";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(1280, 860), "Crazy Colors", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	//window.setFramerateLimit(60);

	Slider slider;
	ControlPanel controlPanel(slider);

	Grid grid({
		Hexagon("RGB", &Conversions::fromRGB, [&slider](auto v) { return v * slider.getValue(); }),
		Hexagon("CMY", &Conversions::fromCMY, [&slider](auto v) { return v * slider.getValue(); }),
		Hexagon("HSL", &Conversions::fromHSL, [&slider](auto v) { return sf::Vector3f(v.x, v.y, v.z * slider.getValue()); }),
		Hexagon("HSV", &Conversions::fromHSV, [&slider](auto v) { return sf::Vector3f(v.x, v.y, v.z * slider.getValue()); })
		},
		controlPanel,
		10.f,
		10.f
	);

	sf::Clock frameClock, aroundHalfSecondClock;
	std::vector<sf::Int64> frameTimes;

	aroundHalfSecondClock.restart();

	grid.resize(window.getSize().x, window.getSize().y);

	while (window.isOpen()) {
		frameClock.restart();

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
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Down:
				case sf::Keyboard::Left:
					slider -= 0.1f;
					grid.markModified();
					break;
				case sf::Keyboard::Right:
				case sf::Keyboard::Up:
					slider += 0.1f;
					grid.markModified();
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
			case sf::Event::MouseMoved:
				if(slider.handleMouseEvent(event))
					grid.markModified();
				break;
			}

		}

		grid.regenerateTextures();

		frameTimes.push_back(frameClock.restart().asMicroseconds());
		if (aroundHalfSecondClock.getElapsedTime().asSeconds() >= 0.5f && frameTimes.size() >= 1) {
			controlPanel.setTimer(std::reduce(frameTimes.begin(), frameTimes.end()) / frameTimes.size());
			frameTimes.clear();
			aroundHalfSecondClock.restart();
		}

		window.clear(sf::Color(32, 32, 32));
		window.draw(grid);
		window.display();
	}

	return 0;
}