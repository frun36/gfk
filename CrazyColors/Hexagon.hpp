#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

extern sf::Font font;

class Hexagon : public sf::Drawable {
protected:
	sf::Vector2f _topLeft, _bottomRight, _center;
	sf::Text _title;
	std::array<sf::Text, 3> _labels;
	sf::ConvexShape _polygon;
	sf::RectangleShape _border;
	bool getCoordinatesWithinRhombus(size_t rhombusOriginPoint, const sf::Vector2f& p, sf::Vector2f& result) const;
	sf::Vector3f getHexCoordinates(const sf::Vector2f& p) const;
public:
	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	Hexagon(sf::Vector2f topLeft, sf::Vector2f bottomRight, std::string title, std::array<std::string, 3> labels);

	void drawBorders(sf::RenderTarget& target) const;

	virtual void fill(sf::RenderTarget& target) const = 0;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		drawBorders(target);
		fill(target);
	}
};

class RGB : public Hexagon {
public:
	RGB(sf::Vector2f topLeft, sf::Vector2f bottomRight) : Hexagon(topLeft, bottomRight, "RGB", { "R", "G", "B" }) {}

	void fill(sf::RenderTarget& target) const override {}
};

#endif