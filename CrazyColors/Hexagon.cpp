#include "Hexagon.hpp"

void Hexagon::resize(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
	_topLeft = topLeft;
	_bottomRight = bottomRight;
	_center = (_topLeft + _bottomRight) * 0.5f;

	float radius = (_center.y - _topLeft.y) * 0.75f;
	float angleRad;

	for (size_t i = 0; i < 6; i++) {
		angleRad = 2 * 3.14159f * i / 6.f + 3.14159f * 0.5f;
		_polygon.setPoint(i, sf::Vector2f(
			_center.x + cos(angleRad) * radius,
			_center.y + sin(angleRad) * radius
		));
	}

	_border.setPosition(topLeft);
	_border.setSize(bottomRight - topLeft);

	_title.setCharacterSize(32);
	_title.setPosition(topLeft + sf::Vector2f(8, 0));

	_labels[0].setCharacterSize(32);
	_labels[0].setPosition(sf::Vector2f(
		_center.x - 8,
		_center.y - radius * 1.2
	));

	_labels[1].setCharacterSize(32);
	_labels[1].setPosition(sf::Vector2f(
		_center.x - radius * 1.1 * sqrt(3) * 0.5 - 8,
		_center.y + radius * 1.1 * sqrt(3) * 0.25
	));

	_labels[2].setCharacterSize(32);
	_labels[2].setPosition(sf::Vector2f(
		_center.x + radius * 1.1 * sqrt(3) * 0.5 - 8,
		_center.y + radius * 1.1 * sqrt(3) * 0.25
	));
}

Hexagon::Hexagon(sf::Vector2f topLeft, sf::Vector2f bottomRight, std::string title, std::array<std::string, 3> labels) : _polygon(6), _border(topLeft - bottomRight), _title() {
	resize(topLeft, bottomRight);

	_polygon.setFillColor(sf::Color::Transparent);
	_polygon.setOutlineColor(sf::Color::White);
	_polygon.setOutlineThickness(3.f);

	_border.setFillColor(sf::Color(16, 16, 16));
	_border.setOutlineColor(sf::Color(64, 64, 64));
	_border.setOutlineThickness(1.f);

	_title.setFont(font);
	_title.setString(title);
	_title.setFillColor(sf::Color(220, 220, 220));

	for (size_t i = 0; i < 3; i++) {
		_labels[i].setFont(font);
		_labels[i].setString(labels[i]);
		_labels[i].setFillColor(sf::Color(220, 220, 220));
	}
}

void Hexagon::drawBorders(sf::RenderTarget& target) const {
	target.draw(_border);
	target.draw(_polygon);
	target.draw(_title);

	for (auto l : _labels) {
		target.draw(l);
	}
}
