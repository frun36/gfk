#include "Model.hpp"
#include "Line.hpp"

void Model::draw(wxDC& dc, int width, int height) const {
	//dc.DrawRectangle(50, 50, 100, 100);

	Matrix4 m = Matrix4::identity()
		.rotateX(_config.getRotX())
		.rotateY(_config.getRotY())
		.rotateZ(_config.getRotZ())
		.scale(_config.getScaleX(), _config.getScaleY(), _config.getScaleZ())
		.translate(_config.getTransX(), _config.getTransY(), _config.getTransZ())
		;

	for (auto& s : _mesh.segments) {
		dc.SetPen(wxPen(wxColour(s.color.r, s.color.g, s.color.b)));

		Line line = Line::fromProjectedSegment(s.transformed(m).clipped(2), 2);
		/*line.x0 *= 1;
		line.y0 *= 1;
		line.x1 *= 1;
		line.y1 *= 1;
		*/
		line.x0 += 0.5 * width;
		line.y0 += 0.5 * height;
		line.x1 += 0.5 * width;
		line.y1 += 0.5 * height;
		line.draw(dc);
	}
}
