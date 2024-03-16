#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Hexagon : public sf::Drawable {
protected:
	sf::Vector2f _topLeft, _bottomRight, _center;
	sf::ConvexShape _polygon;
	sf::RectangleShape _border;
public:
	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	Hexagon(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	void drawBorders(sf::RenderTarget& target) const;
};

class RGB : public Hexagon {
public:
	RGB(sf::Vector2f topLeft, sf::Vector2f bottomRight) : Hexagon(topLeft, bottomRight) {}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		drawBorders(target);
	}
};

#endif