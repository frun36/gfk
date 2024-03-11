#ifndef FIELD_HPP
#define FIELD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

enum State { EMPTY, WALL, FLOOR, TARGET, CHEST };

class Field : public sf::Drawable {
private:
	State _state = State::EMPTY;
	float _size = 100;
	float _x = 100;
	float _y = 200;
public:
	Field(float x = 0, float y = 0, State state = State::EMPTY) : _x(x), _y(y), _state(state) {}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		std::cout << "Drawing field " << _state << '\n';
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

		sf::RectangleShape shape(sf::Vector2f(_size, _size));
		shape.setFillColor(color);
		shape.setPosition(_x, _y);
		target.draw(shape);
	}
};

#endif