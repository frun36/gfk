#ifndef UTIL_HPP
#define UTIL_HPP

#include <SFML/System.hpp>

inline float length(const sf::Vector2f& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

inline float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b) {
	return a.x * b.x + a.y * b.y;
}

#endif
