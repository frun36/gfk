#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <SFML/Graphics.hpp>

class Conversions {
private:
	static float floatMod(float a, float b) {
		while (a > b) a -= b;
		return a;
	}

	static sf::Vector3f hueToRGB(float h, float c, float x) {
		if (h < 60.f) return sf::Vector3f(c, x, 0);
		if (h < 120.f) return sf::Vector3f(x, c, 0);
		if (h < 180.f) return sf::Vector3f(0, c, x);
		if (h < 240.f) return sf::Vector3f(0, x, c);
		if (h < 300.f) return sf::Vector3f(x, 0, c);
		return sf::Vector3f(c, 0, x);
	}

public:
	static sf::Color fromRGB(sf::Vector3f vec) {
		return sf::Color(
			static_cast<sf::Uint8>(255.f * vec.x),
			static_cast<sf::Uint8>(255.f * vec.y),
			static_cast<sf::Uint8>(255.f * vec.z)
		);
	}

	static sf::Color fromCMY(sf::Vector3f vec) {
		return sf::Color(
			255 - static_cast<sf::Uint8>(255.f * vec.x),
			255 - static_cast<sf::Uint8>(255.f * vec.y),
			255 - static_cast<sf::Uint8>(255.f * vec.z)
		);
	}

	static sf::Color fromHSL(sf::Vector3f vec) {
		float h = vec.x * 360.f;

		float c = (1 - fabs(2 * vec.z - 1)) * vec.y;
		float x = c * (1 - fabs(floatMod(h / 60.f, 2.f) - 1));

		float m = vec.z - c / 2;

		sf::Vector3f res = hueToRGB(h, c, x);

		return sf::Color(
			static_cast<sf::Uint8>(255.f * (res.x + m)),
			static_cast<sf::Uint8>(255.f * (res.y + m)),
			static_cast<sf::Uint8>(255.f * (res.z + m))
		);
	}

	static sf::Color fromHSV(sf::Vector3f vec) {
		float h = vec.x * 360.f;

		float c = vec.z * vec.y;
		float x = c * (1 - fabs(floatMod(h / 60.f, 2.f) - 1));

		float m = vec.z - c;

		sf::Vector3f res = hueToRGB(h, c, x);

		return sf::Color(
			static_cast<sf::Uint8>(255.f * (res.x + m)),
			static_cast<sf::Uint8>(255.f * (res.y + m)),
			static_cast<sf::Uint8>(255.f * (res.z + m))
		);
	}
};

#endif