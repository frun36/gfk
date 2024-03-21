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
	bool _modified = false;

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

	void resize(unsigned width, unsigned height);

	void regenerateTextures() {
		if (!_modified) return;
		for (auto& tile : _tiles) {
			tile.generateTexture();
		}
		_modified = false;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		for (auto& tile : _tiles) {
			target.draw(tile);
		}

		target.draw(_controlPanel);
	}

	void markModified() {
		_modified = true;
	}

	void handleMouseEvent(sf::Event event) {
		for (auto& tile : _tiles) {
			tile.handleMouseEvent(event);
		}
	}
};

#endif