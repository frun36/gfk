#ifndef LINE_HPP
#define LINE_HPP

#include "Linalg.hpp"
#include <wx/wx.h>

class Line {
public:
	double x0, y0, x1, y1;

	Line(double x0, double y0, double x1 = 0, double y1 = 0) : x0(x0), y0(y0), x1(x1), y1(y1) {}

	Line transform(Matrix m) {
		Vector v0(x0, y0);
		Vector v1(x1, y1);

		v0 = m * v0;
		v1 = m * v1;

		return Line(v0.getX(), v0.getY(), v1.getX(), v1.getY());
	}

	void draw(wxDC& dc) const {
		dc.DrawLine(x0, y0, x1, y1);
	}
};

#endif