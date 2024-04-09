#pragma warning(disable: 4996)

#include "Plot.hpp"

void Plot::draw(wxDC& dc, int width, int height) {
	dc.DrawRectangle(wxRect(0, 0, 200, 200));
}
