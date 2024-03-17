#include "Hexagon.hpp"
#include "util.hpp"

void Hexagon::resize(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
	_topLeft = topLeft;
	_bottomRight = bottomRight;
	_center = (_topLeft + _bottomRight) * 0.5f;

	float radius = (_center.y - _topLeft.y) * 0.75f;
	float angleRad;

	for (size_t i = 0; i < 6; i++) {
		angleRad = 2.f * 3.14159f * i / 6.f + 3.14159f * 0.5f;
		_polygon.setPoint(i, sf::Vector2f(
			_center.x + cos(angleRad) * radius,
			_center.y - sin(angleRad) * radius
		));
	}

	_border.setPosition(topLeft);
	_border.setSize(bottomRight - topLeft);

	_title.setCharacterSize(32);
	_title.setPosition(topLeft + sf::Vector2f(8, 0));

	_labels[0].setCharacterSize(32);
	_labels[0].setPosition(sf::Vector2f(
		_center.x - 8.f,
		_center.y - radius * 1.2f
	));

	_labels[1].setCharacterSize(32);
	_labels[1].setPosition(sf::Vector2f(
		_center.x - radius * 1.1f * static_cast<float>(sqrt(3)) * 0.5f - 8.f,
		_center.y + radius * 1.1f * static_cast<float>(sqrt(3)) * 0.25f
	));

	_labels[2].setCharacterSize(32);
	_labels[2].setPosition(sf::Vector2f(
		_center.x + radius * 1.1f * static_cast<float>(sqrt(3)) * 0.5f - 8.f,
		_center.y + radius * 1.1f * static_cast<float>(sqrt(3)) * 0.25f
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

	sf::Vector3f res;
	//for (size_t i = 0; i < 6; i++) {
	//	if(getCoordinatesWithinRhombus(i, _center, res))
	//		std::cout << i << ": " << res.x << " " << res.y << " " << res.z << "\n";
	//}

	sf::CircleShape c1;
	c1.setRadius(10);

	for (size_t i = 0; i < 64; i++) {
		for (size_t j = 0; j < 128; j++) {
			c1.setPosition(_polygon.getPoint(0) + sf::Vector2f(200 - sqrt(3) * 2. * j, 20. * i));
			/*size_t j = 1;
			while (!getCoordinatesWithinRhombus(j, c1.getPosition(), res)) { j += 2; }*/
			//getCoordinatesWithinRhombus(0, c1.getPosition(), res);
			//std::cout << res.x << " " << res.y << " " << res.z << "\n";
			res = getHexCoordinates(c1.getPosition());
			c1.setFillColor(sf::Color(res.x * 255, res.y * 255, res.z * 255));
			target.draw(c1);
		}
		
	}

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

sf::Vector3f Hexagon::getHexCoordinates(const sf::Vector2f& p) const
{
	sf::Vector2f result;
	if (getCoordinatesWithinRhombus(0, p, result)) {
		return sf::Vector3f(1, result.y, result.x);
	}
	if (getCoordinatesWithinRhombus(2, p, result)) {
		return sf::Vector3f(result.x, 1, result.y);
	} 
	if (getCoordinatesWithinRhombus(4, p, result)) {
		return sf::Vector3f(result.y, result.x, 1);
	}
	return sf::Vector3f();
}
