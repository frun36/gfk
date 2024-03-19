#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Hexagon.hpp"
#include "ControlPanel.hpp"
#include <array>

class Grid : public sf::Drawable {
private:
	std::array<Hexagon, 4> _tiles;
	sf::Vector2f _topLeft, _bottomRight;
	float _tileSize;
	float _padding;
	float _margin;
	ControlPanel& _controlPanel;

	void updateTileSize() {
		if ((_bottomRight.x - _topLeft.x) / 3 < (_bottomRight.y - _topLeft.y) / 2)
			_tileSize = (_bottomRight.x - _topLeft.x - 2 * _margin - 6 * _padding) / 3;
		else
			_tileSize = (_bottomRight.y - _topLeft.y - 2 * _margin - 4 * _padding) / 2;
	}

public:
	Grid(std::array<Hexagon, 4> tiles, ControlPanel& controlPanel, float padding = 0.f, float margin = 0.f, sf::Vector2f topLeft = sf::Vector2f(), sf::Vector2f bottomRight = sf::Vector2f())
		: _tiles(tiles), _topLeft(topLeft), _bottomRight(bottomRight), _padding(padding), _margin(margin), _tileSize(0.), _controlPanel(controlPanel) {
		updateTileSize();
	}

	void resize(unsigned width, unsigned height) {
		_bottomRight = _topLeft + sf::Vector2f(static_cast<float>(width), static_cast<float>(height));

		updateTileSize();

		_tiles[0].resize(_topLeft + sf::Vector2f(_margin + _padding, _margin + _padding),
			_topLeft + sf::Vector2f(_margin + _padding + _tileSize, _margin + _padding + _tileSize));

		_tiles[1].resize(sf::Vector2f((_bottomRight.x + _topLeft.x) * 0.5f - _tileSize * 0.5f, _topLeft.y + _margin + _padding),
			sf::Vector2f((_bottomRight.x + _topLeft.x) * 0.5f + _tileSize * 0.5f, _topLeft.y + _margin + _padding + _tileSize));

		_tiles[2].resize(sf::Vector2f(_topLeft.x + _margin + _padding, _bottomRight.y - _margin - _padding - _tileSize),
			sf::Vector2f(_topLeft.x + _margin + _padding + _tileSize, _bottomRight.y - _margin - _padding));

		_tiles[3].resize(sf::Vector2f((_bottomRight.x + _topLeft.x) * 0.5f - _tileSize * 0.5f, _bottomRight.y - _margin - _padding - _tileSize),
			sf::Vector2f((_bottomRight.x + _topLeft.x) * 0.5f + _tileSize * 0.5f, _bottomRight.y - _margin - _padding));

		_controlPanel.resize(sf::Vector2f(_bottomRight.x - _margin - _tileSize - _padding, _topLeft.y + _margin + _padding), 
			_bottomRight + sf::Vector2f(-_margin - _padding, -_margin - _padding));
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

		target.draw(_controlPanel);
	}
};

#endif