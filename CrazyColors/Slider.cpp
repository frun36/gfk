#include "Slider.hpp"

Slider::Slider() {
	_knob.setFillColor(sf::Color::Transparent);
	_knob.setOutlineColor(sf::Color(255, 193, 0));
	_knob.setOutlineThickness(4.f);

	_border.setFillColor(sf::Color::Transparent);
	_border.setOutlineColor(sf::Color(220, 220, 220));
	_border.setOutlineThickness(4.f);

	updateKnob();
}

void Slider::generateTexture() {
	unsigned width = static_cast<unsigned>(_bottomRight.x - _topLeft.x);
	unsigned height = static_cast<unsigned>(_bottomRight.y - _topLeft.y);

	std::vector<sf::Uint8> pixelData(4 * width * height);

	size_t currIndex = 0;
	sf::Vector2f currPoint;
	sf::Uint8 currBrightness = 0;

	for (size_t i = static_cast<size_t>(_topLeft.y); i < static_cast<size_t>(_topLeft.y) + height; i++) {
		for (size_t j = static_cast<size_t>(_topLeft.x); j < static_cast<size_t>(_topLeft.x) + width; j++) {
			currBrightness = 255 - static_cast<sf::Uint8>(((i - _topLeft.y) / height) * 255);

			pixelData[currIndex] = currBrightness;
			pixelData[currIndex + 1] = currBrightness;
			pixelData[currIndex + 2] = currBrightness;
			pixelData[currIndex + 3] = currBrightness;

			currIndex += 4;
		}
	}

	sf::Image image;
	image.create(width, height, pixelData.data());

	_texture.create(width, height);
	_texture.update(image);

	_sprite.setTexture(_texture, true);
}

void Slider::resize(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
	_topLeft = topLeft;
	_bottomRight = bottomRight;
	_sprite.setPosition(_topLeft);
	_border.setPosition(_topLeft);
	_border.setSize(_bottomRight - _topLeft);

	updateKnob();
	
	generateTexture();
}

void Slider::updateKnob() {
	_knob.setFillColor(sf::Color(
		static_cast<sf::Uint8>(255 * _value),
		static_cast<sf::Uint8>(255 * _value),
		static_cast<sf::Uint8>(255 * _value)
	));

	_knob.setSize(sf::Vector2f((_bottomRight.x - _topLeft.x) * 1.2f, (_bottomRight.y - _topLeft.y) * 0.025f));
	_knob.setPosition(sf::Vector2f((_topLeft.x + _bottomRight.x - _knob.getSize().x) * 0.5f, _topLeft.y * _value + _bottomRight.y * (1.f - _value) - _knob.getSize().y * 0.5f));
}

Slider& Slider::operator=(float value) {
	_value = value;
	if (_value > 1.f) _value = 1.f;
	else if (_value < 0.f) _value = 0.f;
	updateKnob();
	return *this;
}

bool Slider::handleMouseEvent(sf::Event event) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.x >= _topLeft.x && event.mouseButton.x <= _bottomRight.x && event.mouseButton.y >= _topLeft.y && event.mouseButton.y <= _bottomRight.y) {
			*this = (_bottomRight.y - event.mouseButton.y) / (_bottomRight.y - _topLeft.y);
			_moving = true;
			_lastMouseY = event.mouseButton.y;
			return true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		_moving = false;
		return true;
		break;
	case sf::Event::MouseMoved:
		if (_moving) {
			*this += (_lastMouseY - event.mouseMove.y) / (_bottomRight.y - _topLeft.y);
			_lastMouseY = event.mouseMove.y;
			return true;
		}		
		break;
	case sf::Event::MouseWheelScrolled:
		*this += event.mouseWheelScroll.delta * 0.1f;
		return true;
		break;
	}
	return false;
}

