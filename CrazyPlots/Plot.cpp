#pragma warning(disable: 4996)

#include "Plot.hpp"

void Plot::draw(wxDC& dc, int width, int height) {
	dc.DrawRectangle(wxRect(_config->getX0(), _config->getY0(), _config->getAlpha(), 200));
}
