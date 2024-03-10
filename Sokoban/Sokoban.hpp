#pragma once

#include <SFML/Graphics.hpp>

enum class Field { EMPTY, WALL, FLOOR, TARGET, PLAYER };

class Sokoban : sf::Drawable {
private:
	size_t x, y;
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};