#pragma warning(disable: 4996)

#include "Plot.hpp"
#include "Line.hpp"

void Plot::draw(wxDC& dc, int width, int height) {
	dc.DrawRectangle(100, 100, 100, 100);

	Line(100, 100, 200, 200)
		.transform(Matrix::identity().scale(2, 2).rotate(_config->getAlpha()).fromOrigin(100, 100))
		.draw(dc);
	
}
