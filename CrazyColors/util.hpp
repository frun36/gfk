#ifndef UTIL_HPP
#define UTIL_HPP

#include <SFML/System.hpp>

inline float length(const sf::Vector2f& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

inline float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b) {
	return a.x * b.x + a.y * b.y;
}

inline float detFromColumns(const sf::Vector2f& c1, const sf::Vector2f& c2) {
	return c1.x * c2.y - c2.x * c1.y;
}

inline float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

#endif
