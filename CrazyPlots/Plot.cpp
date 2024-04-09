#pragma warning(disable: 4996)

#include "Plot.hpp"

void Plot::draw(wxDC& dc, int width, int height) {
	dc.DrawRectangle(wxRect(10, 10, 200, 200));
}
