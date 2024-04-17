#pragma once

#include "Transform.hpp"
#include "Geometry.hpp"
#include <wx/wx.h>

class Line {
public:
	double x0, y0, x1, y1;

	Line(double x0, double y0, double x1 = 0, double y1 = 0) : x0(x0), y0(y0), x1(x1), y1(y1) {}

	Line(Point a, Point b) : x0(a.x), y0(a.y), x1(b.x), y1(b.y) {}

	static Line fromProjectedSegment(const Segment& s, double d) {
		Point a = static_cast<Vector4>(s.a).projected(d);
		Point b = static_cast<Vector4>(s.b).projected(d);

		return Line(a, b);
	}

	void draw(wxDC& dc) const {
		dc.DrawLine(x0, y0, x1, y1);
	}
};