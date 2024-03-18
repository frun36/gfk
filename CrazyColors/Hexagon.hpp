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
	sf::Texture _texture;
	sf::Sprite _sprite;


	bool getCoordinatesWithinRhombus(size_t rhombusOriginPoint, const sf::Vector2f& p, sf::Vector2f& result) const;
	sf::Vector3f getHexCoordinates(const sf::Vector2f& p) const;
public:
	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	Hexagon(sf::Vector2f topLeft, sf::Vector2f bottomRight, std::string title);

	void drawBorders(sf::RenderTarget& target) const;

	virtual sf::Color getColorFromHexCoordinates(sf::Vector3f coordinates) const {
		return sf::Color(coordinates.x * 255., coordinates.y * 255., coordinates.z * 255.);
	}

	void generateTexture();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_sprite);
		drawBorders(target);
	}
};

class RGB : public Hexagon {
public:
	RGB(sf::Vector2f topLeft, sf::Vector2f bottomRight) : Hexagon(topLeft, bottomRight, "RGB") {}

	sf::Color getColorFromHexCoordinates(sf::Vector3f coordinates) const override {
		return sf::Color(255, 255, 0.);
	}
};

#endif