#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <SFML/Graphics.hpp>
#include "Field.hpp"
#include "Chest.hpp"
#include "Player.hpp"
#include "Counter.hpp"
#include <iostream>
#include <fstream>
#include <optional>
#include <functional>

class Sokoban : public sf::Drawable {
public:
	enum class Direction {
		DOWN,
		RIGHT,
		UP,
		LEFT,
	};
private:
	unsigned int _x, _y;
	Counter _moveCounter;
	std::vector<std::vector<Field>> _map;
	std::vector<Chest> _chests;
	Player _player;
	float _scale = 1.;

	sf::Vector2i getMotionFromDirection(Direction direction) {
		switch (direction) {
		case Direction::DOWN:
			return sf::Vector2i(0, 1);
		case Direction::RIGHT:
			return sf::Vector2i(1, 0);
		case Direction::UP:
			return sf::Vector2i(0, -1);
		case Direction::LEFT:
			return sf::Vector2i(-1, 0);
		}
	}

	std::optional<std::reference_wrapper<Chest>> getChestAtPosition(sf::Vector2u position) {
		for (auto& chest : _chests) {
			if (chest.getPosition() == position) {
				return std::optional<std::reference_wrapper<Chest>>(chest);
			}
		}
		return std::optional<std::reference_wrapper<Chest>>();
	}

	bool isChestAtPosition(sf::Vector2u position) {
		return getChestAtPosition(position).has_value();
	}

	bool isAvailableForChest(sf::Vector2i position) {
		if (position.x < 0 || position.y < 0 || position.x >= static_cast<int>(_x) || position.y >= static_cast<int>(_y))
			return false;
		return _map[position.y][position.x].isOccupyable() && !isChestAtPosition(sf::Vector2u(position.x, position.y));
	}
public:
	Sokoban(std::string filename) : _moveCounter(Counter()) {
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
		_moveCounter.setScale(_scale);
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
		target.draw(_moveCounter);
	}

	bool checkWin() const {
		for (auto& chest : _chests) {
			if (!_map[chest.getPosition().y][chest.getPosition().x].isTarget()) {
				return false;
			}
		}
		return true;
	}

	void movePlayer(Direction direction) {
		sf::Vector2i motion = getMotionFromDirection(direction);
		sf::Vector2u currentPosition = _player.getPosition();
		int newX = currentPosition.x + motion.x;
		int newY = currentPosition.y + motion.y;

		// Is within map range
		if (newX < 0 || newY < 0 || newX >= static_cast<int>(_x) || newY >= static_cast<int>(_y))
			return;

		sf::Vector2u newPosition = sf::Vector2u(newX, newY);

		// Is occupyable
		if (!_map[newPosition.y][newPosition.x].isOccupyable())
			return;

		// Chest
		if (isChestAtPosition(newPosition)) {
			if (isAvailableForChest(sf::Vector2i(newPosition.x + motion.x, newPosition.y + motion.y)))
				getChestAtPosition(newPosition).value().get().move(motion);
			else
				return;
		}

		_player.move(motion);
		_moveCounter.increment();
	}
};

#endif