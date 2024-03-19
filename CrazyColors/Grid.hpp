#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"
#include <array>

class Grid : public sf::Drawable {
private:
	std::array<Hexagon, 4> _tiles;
	sf::Vector2f _topLeft, _bottomRight;
	float _tileSize;
	float _padding;
	float _margin;

	void updateTileSize() {
		float l = fminf(_bottomRight.x - _topLeft.x, _bottomRight.y - _topLeft.y);
		_tileSize = 0.5f * (l - 2 * _margin - 4 * _padding);
	}

public:
	Grid(std::array<Hexagon, 4> tiles, float padding = 0.f, float margin = 0.f, sf::Vector2f topLeft = sf::Vector2f(), sf::Vector2f bottomRight = sf::Vector2f())
		: _tiles(tiles), _topLeft(topLeft), _bottomRight(bottomRight), _padding(padding), _margin(margin), _tileSize(0.) {
		updateTileSize();
	}

	void resize(unsigned width, unsigned height) {
		_bottomRight = _topLeft + sf::Vector2f(static_cast<float>(width), static_cast<float>(height));

		updateTileSize();

		sf::Vector2f currTopLeft;

		currTopLeft = _topLeft + sf::Vector2f(_margin + _padding, _margin + _padding);
		_tiles[0].resize(currTopLeft, currTopLeft + sf::Vector2f(_tileSize, _tileSize));

		currTopLeft = _topLeft + sf::Vector2f(_margin + 3 * _padding + _tileSize, _margin + _padding);
		_tiles[1].resize(currTopLeft, currTopLeft + sf::Vector2f(_tileSize, _tileSize));

		currTopLeft = _topLeft + sf::Vector2f(_margin + _padding, _margin + 3 * _padding + _tileSize);
		_tiles[2].resize(currTopLeft, currTopLeft + sf::Vector2f(_tileSize, _tileSize));

		currTopLeft = _topLeft + sf::Vector2f(_margin + 3 * _padding + _tileSize, _margin + 3 * _padding + _tileSize);
		_tiles[3].resize(currTopLeft, currTopLeft + sf::Vector2f(_tileSize, _tileSize));
	}

	void regenerateTextures() {
		for (auto& tile : _tiles) {
			tile.generateTexture();
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto& tile : _tiles) {
			target.draw(tile);
		}
	}
};

#endif