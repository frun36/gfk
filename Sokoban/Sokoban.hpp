#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <SFML/Graphics.hpp>
#include "Field.hpp"
#include "Chest.hpp"
#include "Player.hpp"
#include "Direction.hpp"
#include <iostream>
#include <fstream>

class Sokoban : public sf::Drawable {
private:
	unsigned int _x, _y;
	std::vector<std::vector<Field>> _map;
	std::vector<Chest> _chests;
	Player _player;
	float _scale = 1.;
public:
	Sokoban(std::string filename) {
		std::ifstream file(filename);

		if (!file.is_open()) {
			std::cerr << "Unable to open map file " << filename << '\n';
			exit(1);
		}

		std::string line;
		std::string cell;

		// Set chests
		std::getline(file, line);
		unsigned int chestCount = std::stoi(line);
		std::cout << "Chest count: " << chestCount << '\n';
		unsigned int tmpX, tmpY;
		_chests.resize(chestCount, sf::Vector2u(0, 0));
		for (unsigned int i = 0; i < chestCount; i++) {
			std::getline(file, line);
			sscanf_s(line.c_str(), "%u,%u", &tmpX, &tmpY);
			std::cout << "Chest " << i << ": " << tmpX << ", " << tmpY << '\n';
			_chests[i] = sf::Vector2u(tmpX, tmpY);
		}

		// Get player position
		std::getline(file, line);
		sscanf_s(line.c_str(), "%u,%u", &tmpX, &tmpY);
		_player = Player(sf::Vector2u(tmpX, tmpY));
		std::cout << "Player position: " << tmpX << ", " << tmpY << '\n';

		// Set dimensions
		std::getline(file, line);
		sscanf_s(line.c_str(), "%u,%u", &_x, &_y);
		std::cout << "Board dimensions: " << _x << "x" << _y << '\n';
		_map.resize(_y, std::vector<Field>(_x));

		// Initialize fields
		unsigned int xPos = 0;
		unsigned int yPos = 0;
		while (std::getline(file, line)) {
			std::cout << "Row: " << line << '\n';
			xPos = 0;
			for (auto c : line) {
				int value = c - '0';
				_map[yPos][xPos] = Field(sf::Vector2u(xPos, yPos), 100, static_cast<State>(value));
				xPos++;
			}
			yPos++;
		}

		file.close();
	}

	void setScale(sf::Vector2u size) {
		_scale = std::fmin(static_cast<float>(size.x) / _x, static_cast<float>(size.y) / _y);
		for (auto& chest : _chests) {
			chest.setScale(_scale);
		}

		for (auto& row : _map) {
			for (auto& field : row) {
				field.setScale(_scale);
			}
		}

		_player.setScale(_scale);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto& row : _map) {
			for (auto& field : row) {
				target.draw(field);
			}
		}

		for (auto& chest : _chests) {
			target.draw(chest);
		}

		target.draw(_player);
	}

	void movePlayer(Direction direction) {
		_player.move(direction);
	}
};

#endif