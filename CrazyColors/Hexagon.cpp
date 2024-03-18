#include "Hexagon.hpp"
#include "util.hpp"

void Hexagon::resize(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
	_topLeft = topLeft;
	_bottomRight = bottomRight;
	_center = (_topLeft + _bottomRight) * 0.5f;

	// Generate hexagon
	float radius = (_center.y - _topLeft.y) * 0.75f;
	float angleRad;

	for (size_t i = 0; i < 6; i++) {
		angleRad = 2.f * 3.14159f * i / 6.f + 3.14159f * 0.5f;
		_polygon.setPoint(i, sf::Vector2f(
			_center.x + cos(angleRad) * radius,
			_center.y - sin(angleRad) * radius
		));
	}

	// Square border
	_border.setPosition(topLeft);
	_border.setSize(bottomRight - topLeft);

	// Texture sprite
	_sprite.setPosition(topLeft);

	// Text
	_title.setPosition(topLeft + sf::Vector2f(8, 0));

	_labels[0].setPosition(sf::Vector2f(
		_center.x - 8.f,
		_center.y - radius * 1.2f
	));

	_labels[1].setPosition(sf::Vector2f(
		_center.x - radius * 1.1f * static_cast<float>(sqrt(3)) * 0.5f - 8.f,
		_center.y + radius * 1.1f * static_cast<float>(sqrt(3)) * 0.25f
	));

	_labels[2].setPosition(sf::Vector2f(
		_center.x + radius * 1.1f * static_cast<float>(sqrt(3)) * 0.5f - 8.f,
		_center.y + radius * 1.1f * static_cast<float>(sqrt(3)) * 0.25f
	));

	generateTexture();
}

Hexagon::Hexagon(sf::Vector2f topLeft, sf::Vector2f bottomRight, std::string title, std::function<sf::Color(std::optional<sf::Vector3f>)> getColorFromHexCoordinates)
	: _sprite(_texture), _polygon(6), _border(topLeft - bottomRight), _title(), _getColorFromHexCoordinates(getColorFromHexCoordinates) {
	resize(topLeft, bottomRight);

	_polygon.setFillColor(sf::Color::Transparent);
	_polygon.setOutlineColor(sf::Color(220, 220, 220));
	_polygon.setOutlineThickness(3.f);

	_border.setFillColor(sf::Color::Transparent);
	_border.setOutlineColor(sf::Color(64, 64, 64));
	_border.setOutlineThickness(1.f);

	_title.setFont(font);
	_title.setCharacterSize(32);
	_title.setString(title);
	_title.setFillColor(sf::Color(220, 220, 220));

	for (size_t i = 0; i < 3; i++) {
		_labels[i].setFont(font);
		_labels[i].setCharacterSize(32);
		_labels[i].setString(_title.getString()[i]);
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

void Hexagon::generateTexture() {
	size_t width = static_cast<size_t>((_bottomRight - _topLeft).x);
	size_t height = static_cast<size_t>((_bottomRight - _topLeft).y);

	std::vector<sf::Uint8> pixelData(4 * width * height);

	size_t currIndex = 0;
	sf::Vector2f currPoint;
	sf::Color currColor = sf::Color::Red;

	for (size_t i = _topLeft.y; i < _bottomRight.y; i++) {
		for (size_t j = _topLeft.x; j < _bottomRight.x; j++) {
			currPoint.y = static_cast<float>(i);
			currPoint.x = static_cast<float>(j);
			currColor = _getColorFromHexCoordinates(
				getHexCoordinates(currPoint)
			);

			pixelData[currIndex] = currColor.r;
			pixelData[currIndex + 1] = currColor.g;
			pixelData[currIndex + 2] = currColor.b;
			pixelData[currIndex + 3] = currColor.a;

			currIndex += 4;
		}
	}


	sf::Image image;
	image.create(width, height, pixelData.data());

	_texture.create(width, height);
	_texture.update(image);

	_sprite.setTexture(_texture, true);
}

bool Hexagon::getCoordinatesWithinRhombus(size_t rhombusOriginPoint, const sf::Vector2f& p, sf::Vector2f& result) const {
	sf::Vector2f originPoint = _polygon.getPoint(rhombusOriginPoint);
	sf::Vector2f rightPoint = _polygon.getPoint((rhombusOriginPoint + 1) % 6);
	sf::Vector2f leftPoint = _polygon.getPoint((rhombusOriginPoint + 5) % 6);

	sf::Vector2f rightArm = rightPoint - originPoint;
	sf::Vector2f leftArm = leftPoint - originPoint;
	sf::Vector2f pointArm = p - originPoint;

	float sideLength = length(rightArm);

	float det = detFromColumns(leftArm, rightArm);

	result = sf::Vector2f(
		detFromColumns(pointArm, rightArm) / det,
		detFromColumns(leftArm, pointArm) / det
	);

	return (result.x <= 1.f) && (result.y <= 1.f) && (result.x >= 0) && (result.y >= 0);
}

std::optional<sf::Vector3f> Hexagon::getHexCoordinates(const sf::Vector2f& p) const
{
	sf::Vector2f result;
	if (getCoordinatesWithinRhombus(0, p, result)) {
		return std::optional(sf::Vector3f(1, result.y, result.x));
	}
	if (getCoordinatesWithinRhombus(2, p, result)) {
		return std::optional(sf::Vector3f(result.x, 1, result.y));
	}
	if (getCoordinatesWithinRhombus(4, p, result)) {
		return std::optional(sf::Vector3f(result.y, result.x, 1));
	}
	return std::optional<sf::Vector3f>();
}
