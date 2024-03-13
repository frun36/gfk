#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <SFML/Graphics.hpp>

class Counter : public sf::Drawable {
private:
	unsigned int _value;
	sf::Text _text;
	float _scale;

public:
	void increment() {
		_value++;
		_text.setString(std::to_string(_value));
	}

	void setScale(float scale) {
		_scale = scale;
		_text.setCharacterSize(scale * 0.75f);
		_text.setPosition(scale * 0.1f, 0);
	}

	Counter(float scale = 1) : _value(0), _scale(scale) {
		sf::Font *font = new sf::Font();
		if (!font->loadFromFile("arial.ttf")) {
			std::cerr << "Failed to load font file!\n";
			exit(1);
		}
		_text.setFont(*font);
		_text.setCharacterSize(scale * 0.75);
		_text.setFillColor(sf::Color(255, 0, 0));
		_text.setString(std::to_string(0));
		_text.setPosition(scale * 0.1f, 0);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_text);
	}
};

#endif