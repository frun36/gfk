#include "Grid.hpp"

void Grid::resize(unsigned width, unsigned height) {
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
