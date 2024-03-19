#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

class Slider : public sf::Drawable {
private:
	float _value = 1.;
	sf::Vector2f _topLeft, _bottomRight;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::RectangleShape _border;

public:
	void generateTexture() {
		unsigned width = _bottomRight.x - _topLeft.x;
		unsigned height = _bottomRight.y - _topLeft.y;

		std::vector<sf::Uint8> pixelData(4 * width * height);

		size_t currIndex = 0;
		sf::Vector2f currPoint;
		sf::Uint8 currBrightness = 0;

		for (size_t i = static_cast<size_t>(_topLeft.y); i < static_cast<size_t>(_topLeft.y) + height; i++) {
			for (size_t j = static_cast<size_t>(_topLeft.x); j < static_cast<size_t>(_topLeft.x) + width; j++) {
				currBrightness = ((i - _topLeft.y) / height) * 255;

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

		_border.setFillColor(sf::Color::Transparent);
		_border.setOutlineColor(sf::Color(220, 220, 220));
		_border.setOutlineThickness(4.f);
	}

	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
		_topLeft = topLeft;
		_bottomRight = bottomRight;
		_sprite.setPosition(_topLeft);
		_border.setPosition(_topLeft);
		_border.setSize(_bottomRight - _topLeft);

		generateTexture();
	}

	Slider& operator+=(float increment) {
		_value += increment;
		if (_value > 1.f) _value = 1.f;
		else if (_value < 0.f) _value = 0.f;
		return *this;
	}

	Slider& operator-=(float increment) {
		return this->operator+=(-increment);
	}

	float getValue() const {
		return _value;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_sprite);
		target.draw(_border);
	}
};

#endif