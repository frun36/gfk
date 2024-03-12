#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

static constexpr float PLAYER_RATIO = 0.9f;

class Player : public sf::Drawable {
private:
	sf::Vector2u _position;
	float _scale;
	sf::CircleShape _circle;

	void updateCirclePosition() {
		_circle.setPosition(sf::Vector2f(_scale * _position.x + _scale * (1.f - PLAYER_RATIO) * 0.5f,
			_scale * _position.y + _scale * (1.f - PLAYER_RATIO) * 0.5f));
	}
public:
	Player(sf::Vector2u position = sf::Vector2u(0, 0), float scale = 1.) : _position(position), _scale(scale) {
		_circle = sf::CircleShape();
		_circle.setFillColor(sf::Color(255, 217, 102));
	}

	void setScale(float scale) {
		_scale = scale;
		_circle.setRadius(_scale * PLAYER_RATIO * 0.5f);
		updateCirclePosition();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_circle);
	}

	void move(sf::Vector2i motion) {
		_position.x += motion.x;
		_position.y += motion.y;
		updateCirclePosition();
	}

	const sf::Vector2u& getPosition() {
		return _position;
	}
};

#endif