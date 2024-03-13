#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <SFML/Graphics.hpp>

class Counter : public sf::Drawable {
private:
	unsigned int _value;
	sf::Text _text;
	float _scale;
	sf::Vector2i _offset;

public:
	void increment() {
		_value++;
		_text.setString(std::to_string(_value));
	}

	void setScale(float scale, sf::Vector2i offset) {
		_scale = scale;
		_offset = offset;
		_text.setCharacterSize(static_cast<unsigned int>(scale * 0.75f));
		_text.setPosition(scale * 0.1f + offset.x, 0.f + offset.y);
	}

	Counter(float scale = 1, sf::Vector2i offset = sf::Vector2i(0, 0)) : _value(0), _scale(scale), _offset(offset) {
		sf::Font *font = new sf::Font();
		if (!font->loadFromFile("arial.ttf")) {
			std::cerr << "Failed to load font file!\n";
			exit(1);
		}
		_text.setFont(*font);
		_text.setCharacterSize(static_cast<unsigned int>(scale * 0.75));
		_text.setFillColor(sf::Color(255, 0, 0));
		_text.setString(std::to_string(0));
		_text.setPosition(scale * 0.1f, 0);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_text);
	}
};

#endif