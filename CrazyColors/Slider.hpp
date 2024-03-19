#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

class Slider : sf::Drawable {
private:
	float _value = 1.;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

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
};

#endif