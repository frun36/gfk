#ifndef CONTROLPANEL_HPP
#define CONTROLPANEL_HPP

#include <SFML/Graphics.hpp>
#include "Slider.hpp"
#include <string>

extern sf::Font font;

class ControlPanel : public sf::Drawable {
private:
	sf::Vector2f _topLeft, _bottomRight;
	Slider& _slider;
	sf::RectangleShape _border;
	sf::Text _timer;

public:
	ControlPanel(Slider& slider, sf::Vector2f topLeft = sf::Vector2f(), sf::Vector2f bottomRight = sf::Vector2f())
		: _slider(slider), _topLeft(topLeft), _bottomRight(bottomRight), _border(bottomRight - topLeft), _timer() {
		_timer.setFont(font);
		_timer.setCharacterSize(32);
		_timer.setString("-");
		_timer.setFillColor(sf::Color(220, 220, 220));

		_border.setFillColor(sf::Color(16, 16, 16));
		_border.setOutlineColor(sf::Color(64, 64, 64));
		_border.setOutlineThickness(1.f);
	}

	void resize(sf::Vector2f topLeft, sf::Vector2f bottomRight) {
		_topLeft = topLeft;
		_bottomRight = bottomRight;

		_slider.resize(topLeft + sf::Vector2f(0.4f * (bottomRight - topLeft).x, 0.3f * (bottomRight - topLeft).x), 
			bottomRight - sf::Vector2f(0.4f * (bottomRight - topLeft).x, 0.3f * (bottomRight - topLeft).x));

		_border.setPosition(topLeft);
		_border.setSize(bottomRight - topLeft);

		_timer.setPosition(topLeft + sf::Vector2f(8, 0));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_border);
		target.draw(_slider);
		target.draw(_timer);
	}

	void setTimer(sf::Int64 time) {
		_timer.setString(std::to_string(time) + " us");
	}
};

#endif