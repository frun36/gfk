#ifndef CHEST_HPP
#define CHEST_HPP

#include <SFML/Graphics.hpp>

static constexpr float RATIO = 0.75;

class Chest : public sf::Drawable {
private:
	sf::Vector2u _position;
	float _scale;
	sf::RectangleShape _rect;
public:
	Chest(sf::Vector2u position, float scale = 1.) : _position(position), _scale(scale) {
		_rect = sf::RectangleShape();
		_rect.setFillColor(sf::Color(116, 71, 0));
	}

	void setScale(float scale) {
		_scale = scale;
		_rect.setSize(sf::Vector2f(_scale * RATIO, _scale * RATIO));
		_rect.setPosition(sf::Vector2f(_scale * _position.x + _scale * (1 - RATIO) / 2,
			_scale * _position.y + _scale * (1 - RATIO) / 2));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_rect);
	}
};

#endif