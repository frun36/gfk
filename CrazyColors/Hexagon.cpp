#include "Hexagon.hpp"
#include "util.hpp"

Hexagon::Hexagon(std::string title,
	std::function<sf::Color(sf::Vector3f)> convertColor,
	std::function<sf::Vector3f(sf::Vector3f)> modifyColor,
	sf::Vector2f topLeft,
	sf::Vector2f bottomRight
) : _sprite(_texture), _polygon(6), _topLeft(topLeft), _bottomRight(bottomRight), _border(bottomRight - topLeft), _convertColor(convertColor), _modifyColor(modifyColor) {
	_polygon.setFillColor(sf::Color::Transparent);
	_polygon.setOutlineColor(sf::Color(220, 220, 220));
	_polygon.setOutlineThickness(4.f);

	_border.setFillColor(sf::Color(16, 16, 16));
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
	_sprite.setPosition(_center * 0.25f + _topLeft * 0.75f);

	// Text
	_title.setPosition(topLeft + sf::Vector2f(8, 0));

	_labels[0].setPosition(sf::Vector2f(
		_center.x - 8.f,
		_center.y - (radius + 48)
	));

	_labels[1].setPosition(sf::Vector2f(
		_center.x - (radius + 24) * static_cast<float>(sqrt(3)) * 0.5f - 8.f,
		_center.y + (radius + 24) * static_cast<float>(sqrt(3)) * 0.25f
	));

	_labels[2].setPosition(sf::Vector2f(
		_center.x + (radius + 24) * static_cast<float>(sqrt(3)) * 0.5f - 8.f,
		_center.y + (radius + 24) * static_cast<float>(sqrt(3)) * 0.25f
	));

	generateTexture();
}

void Hexagon::generateTexture() {
	unsigned width = static_cast<unsigned>((_bottomRight - _topLeft).x * 0.75f);
	unsigned height = static_cast<unsigned>((_bottomRight - _topLeft).y * 0.75f);

	sf::Vector2f offset = _center * 0.25f + _topLeft * 0.75f;

	std::vector<sf::Uint8> pixelData(4 * width * height);

	size_t currIndex = 0;
	sf::Vector2f currPoint;
	sf::Color currColor;

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			currPoint.y = static_cast<float>(i) + offset.y;
			currPoint.x = static_cast<float>(j) + offset.x;
			currColor = getColorFromHexCoordinates(
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

void Hexagon::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_border);
	target.draw(_title);

	for (auto l : _labels) {
		target.draw(l);
	}

	target.draw(_sprite);

	target.draw(_polygon);
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

	return (result.x <= 1.00001f) && (result.y <= 1.00001f) && (result.x >= -0.00001) && (result.y >= -0.00001);
}

std::optional<sf::Vector3f> Hexagon::getHexCoordinates(const sf::Vector2f& p) const {
	float d = distance(p, _polygon.getPoint(0));
	float d2 = distance(p, _polygon.getPoint(2));
	float d4 = distance(p, _polygon.getPoint(4));
	size_t closestPoint = 0;
	if (d2 < d) closestPoint = 2;
	if (d4 < d2 && d4 < d) closestPoint = 4;

	sf::Vector2f result;
	bool control = true;
	std::optional<sf::Vector3f> returnValue;
	switch (closestPoint) {
	case 0:
		control = control && getCoordinatesWithinRhombus(0, p, result);
		returnValue = std::optional(_modifyColor(sf::Vector3f(1, result.y, result.x)));
		break;
	case 2:
		control = control && getCoordinatesWithinRhombus(2, p, result);
		returnValue = std::optional(_modifyColor(sf::Vector3f(result.x, 1, result.y)));
		break;
	case 4:
		control = control && getCoordinatesWithinRhombus(4, p, result); 
		returnValue = std::optional(_modifyColor(sf::Vector3f(result.y, result.x, 1)));
		break;
	}
	return control ? returnValue : std::optional<sf::Vector3f>();
}
