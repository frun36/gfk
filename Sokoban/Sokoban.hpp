#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <SFML/Graphics.hpp>
#include "Field.hpp"
#include <iostream>
#include <fstream>

class Sokoban : public sf::Drawable {
private:
	size_t _x, _y;
	std::vector<std::vector<Field>> _map;
public:
	Sokoban(std::string filename) : _x(2), _y(1) {
		std::ifstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Unable to open map file " << filename << '\n';
			exit(1);
		}

		std::string line;
		std::string cell;

		// Set dimensions
		std::getline(file, line);
		sscanf_s(line.c_str(), "%zd,%zd", &_x, &_y);
		std::cout << _x << ' ' << _y << '\n';
		_map.resize(_y, std::vector<Field>(_x));

		// Initialize fields
		size_t x_pos = 0;
		size_t y_pos = 0;
		while (std::getline(file, line)) {
			std::cout << "got line: " << line << '\n';
			x_pos = 0;
			for (auto c : line) {
				size_t value = c - '0';
				std::cout << value << '\n';
				_map[y_pos][x_pos] = Field(x_pos*100, y_pos*100, static_cast<State>(value));
				x_pos++;
			}
			y_pos++;
		}

		file.close();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto &row : _map) {
			for (auto& field : row) {
				target.draw(field);
			}
		}
	}
};

#endif