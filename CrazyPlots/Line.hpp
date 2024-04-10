#ifndef LINE_HPP
#define LINE_HPP

#include "Linalg.hpp"
#include <wx/wx.h>

class Line {
private:
	double _x0, _y0, _x1, _y1;

public:
	Line(double x0, double y0, double x1, double y1) : _x0(x0), _y0(y0), _x1(x1), _y1(y1) {}

	Line transform(Matrix m) {
		Vector v0(_x0, _y0);
		Vector v1(_x1, _y1);

		v0 = m * v0;
		v1 = m * v1;

		return Line(v0.getX(), v0.getY(), v1.getX(), v1.getY());
	}

	void draw(wxDC& dc) {
		dc.DrawLine(_x0, _y0, _x1, _y1);
	}
};

#endif