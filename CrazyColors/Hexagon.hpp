#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <functional>
#include <optional>
#include <string>
#include "conversions.hpp"

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
	std::function<sf::Color(sf::Vector3f)> _convertColor;
	std::function<sf::Vector3f(sf::Vector3f)> _modifyColor;
	sf::Text _clickInfo;
	bool _isClickable;

	sf::Color getColorFromHexCoordinates(std::optional<sf::Vector3f> vec) {
		return vec.has_value() ? _convertColor(vec.value()) : sf::Color::Transparent;
	}

	bool getCoordinatesWithinRhombus(size_t rhombusOriginPoint, const sf::Vector2f& p, sf::Vector2f& result) const;
	std::optional<sf::Vector3f> getHexCoordinates(const sf::Vector2f& p) const;

	void handleMouseClick(sf::Vector2i mousePosition);
public:
	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	Hexagon(std::string title,
		std::function<sf::Color(sf::Vector3f)> convertColor,
		std::function<sf::Vector3f(sf::Vector3f)> modifyColor,
		bool isClickable = false,
		sf::Vector2f topLeft = sf::Vector2f(),
		sf::Vector2f bottomRight = sf::Vector2f()
	);

	void generateTexture();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void handleMouseEvent(sf::Event event);
};

#endif