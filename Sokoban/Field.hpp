#ifndef FIELD_HPP
#define FIELD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

enum State { EMPTY, WALL, FLOOR, TARGET, CHEST };

class Field : public sf::Drawable {
private:
	State _state = State::EMPTY;
	sf::Vector2u _position;
	sf::RectangleShape _rect;
	float _scale = 1.;
public:
	Field(sf::Vector2u position = sf::Vector2u(0, 0), float scale = 1, State state = State::EMPTY) : _position(position), _scale(scale), _state(state) {
		_rect = sf::RectangleShape(sf::Vector2f(scale, scale));
		_rect.setPosition(sf::Vector2f(_scale * _position.x, _scale * _position.y));
		sf::Color color;
		switch (_state) {
		case State::EMPTY:
			color = sf::Color(0, 0, 0);
			break;
		case State::WALL:
			color = sf::Color(128, 128, 128);
			break;
		case State::FLOOR:
			color = sf::Color(200, 200, 200);
			break;
		case State::TARGET:
			color = sf::Color(0, 255, 0);
			break;
		case State::CHEST:
			color = sf::Color(255, 255, 0);
			break;
		}

		_rect.setFillColor(color);
	}

	void setScale(float scale) {
		_scale = scale;
		_rect.setSize(sf::Vector2f(_scale, _scale));
		_rect.setPosition(sf::Vector2f(_scale * _position.x, _scale * _position.y));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_rect);
	}

	bool isOccupyable() const {
		return _state != State::WALL && _state != State::EMPTY;
	}

	bool isTarget() const {
		return _state == State::TARGET;
	}
};

#endif