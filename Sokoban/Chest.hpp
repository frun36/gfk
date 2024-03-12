#ifndef CHEST_HPP
#define CHEST_HPP

#include <SFML/Graphics.hpp>

static constexpr float CHEST_RATIO = 0.75;

class Chest : public sf::Drawable {
private:
	sf::Vector2u _position;
	float _scale;
	sf::RectangleShape _rect;

	void updateRectPosition() {
		_rect.setPosition(sf::Vector2f(_scale * _position.x + _scale * (1.f - CHEST_RATIO) * 0.5f,
			_scale * _position.y + _scale * (1.f - CHEST_RATIO) * 0.5f));
	}

public:
	Chest(sf::Vector2u position = sf::Vector2u(0, 0), float scale = 1.) : _position(position), _scale(scale) {
		_rect = sf::RectangleShape();
		_rect.setFillColor(sf::Color(116, 71, 0));
	}

	void setScale(float scale) {
		_scale = scale;
		_rect.setSize(sf::Vector2f(_scale * CHEST_RATIO, _scale * CHEST_RATIO));
		updateRectPosition();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_rect);
	}

	void move(sf::Vector2i motion) {
		_position.x += motion.x;
		_position.y += motion.y;
		updateRectPosition();
	}

	const sf::Vector2u& getPosition() const {
		return _position;
	}
};

#endif