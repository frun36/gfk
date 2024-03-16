#include "Hexagon.hpp"

void Hexagon::resize(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
	_topLeft = topLeft;
	_bottomRight = bottomRight;
	_center = (_topLeft + _bottomRight) * 0.5f;

	float radius = (_topLeft.y - _center.y) * 0.75f;
	float angleRad;

	for (size_t i = 0; i < 6; i++) {
		angleRad = 2 * 3.14159f * i / 6 + 3.14159f * 0.5;
		_polygon.setPoint(i, sf::Vector2f(
			_center.x + cos(angleRad) * radius,
			_center.y + sin(angleRad) * radius
		));
	}

	_border.setPosition(topLeft);
	_border.setSize(bottomRight - topLeft);
}

Hexagon::Hexagon(sf::Vector2f topLeft, sf::Vector2f bottomRight) : _polygon(6), _border(topLeft - bottomRight) {
	resize(topLeft, bottomRight);

	_polygon.setFillColor(sf::Color::Transparent);
	_polygon.setOutlineColor(sf::Color::White);
	_polygon.setOutlineThickness(3.f);

	_border.setFillColor(sf::Color(16, 16, 16));
	_border.setOutlineColor(sf::Color(64, 64, 64));
	_border.setOutlineThickness(1.f);
}

void Hexagon::drawBorders(sf::RenderTarget& target) const {
	target.draw(_border);
	target.draw(_polygon);
}
