#ifndef CHEST_HPP
#define CHEST_HPP

#include <SFML/Graphics.hpp>

static constexpr float CHEST_RATIO = 0.75;

class Chest : public sf::Drawable {
private:
	sf::Vector2u _position;
	float _scale;
	sf::RectangleShape _rect;
	sf::Vector2i _offset;

	void updateRectPosition() {
		_rect.setPosition(sf::Vector2f(_scale * _position.x + _scale * (1.f - CHEST_RATIO) * 0.5f + _offset.x,
			_scale * _position.y + _scale * (1.f - CHEST_RATIO) * 0.5f + _offset.y));
	}

public:
	Chest(sf::Vector2u position = sf::Vector2u(0, 0), float scale = 1., sf::Vector2i offset = sf::Vector2i(0, 0)) : _position(position), _scale(scale), _offset(offset) {
		_rect = sf::RectangleShape();
		_rect.setFillColor(sf::Color(116, 71, 0));
	}

	void setScale(float scale, sf::Vector2i offset) {
		_scale = scale;
		_offset = offset;
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