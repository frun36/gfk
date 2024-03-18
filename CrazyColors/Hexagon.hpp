#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <functional>
#include <optional>

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
	std::function<sf::Color(std::optional<sf::Vector3f>)> _getColorFromHexCoordinates;


	bool getCoordinatesWithinRhombus(size_t rhombusOriginPoint, const sf::Vector2f& p, sf::Vector2f& result) const;
	std::optional<sf::Vector3f> getHexCoordinates(const sf::Vector2f& p) const;
public:
	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	Hexagon(sf::Vector2f topLeft, sf::Vector2f bottomRight, std::string title, std::function<sf::Color(std::optional<sf::Vector3f>)> getColorFromHexCoordinates);

	void drawBorders(sf::RenderTarget& target) const;

	void generateTexture();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_sprite);
		drawBorders(target);
	}
};

#endif