#include "Plot.hpp"

void Plot::draw(wxDC& dc) const {
	auto transform = Matrix::identity()
		.translate(-250, -250)
		.scale(0.75, 0.75)
		.shear(-0.1, 0)
		.scale(1, (50 + _config.getTilt()) / 200.)
		.translate(250, 250);

	dc.Clear();
	dc.SetPen(*wxTRANSPARENT_PEN);

	for (int x = 0; x < 500; x += _voxelWidth) {
		for (int y = 0; y < 500; y += _voxelWidth) {
			auto p = transform * Vector(x, y);
			float xFun = (x - 250) * 0.01;
			float yFun = (y - 250) * 0.01;
			auto height = 100 * exp(-xFun * xFun - yFun * yFun);
			wxBrush b;
			b.SetColour(height, height, height);
			dc.SetBrush(b);
			dc.DrawRectangle(p.getX(), p.getY(), _voxelWidth, -height);
		}
	}
}
