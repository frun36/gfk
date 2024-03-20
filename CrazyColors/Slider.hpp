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
	sf::RectangleShape _knob;
	bool _moving = false;
	int _lastMouseY = 0;

public:
	Slider();

	void generateTexture();

	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight);

	void updateKnob();

	Slider& operator+=(float increment) {
		return this->operator=(_value + increment);
	}

	Slider& operator-=(float increment) {
		return this->operator=(_value-increment);
	}

	Slider& operator=(float value);

	float getValue() const {
		return _value;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_sprite);
		target.draw(_border);
		target.draw(_knob);
	}

	bool handleMouseEvent(sf::Event event);
};

#endif