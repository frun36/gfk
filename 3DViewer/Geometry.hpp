#pragma once

#include <vector>
#include "Transform.hpp"


struct Point {
	double x, y, z;

	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

	Point(const Vector4& v) : x(v.getX()), y(v.getY()), z(v.getZ()) {}

	operator Vector4() const { return Vector4(x, y, z); }

	Point transformed(const Matrix4& m) const {
		Vector4 v = *this;
		v = m * v;
		return v;
	}
};

struct Color {
	unsigned char r, g, b;

	Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0) : r(r), g(g), b(b) {}
};

struct Segment {
	Point a, b;
	Color color;

	Segment() {}
	Segment(Point a, Point b, Color color) : a(a), b(b), color(color) {}

	Segment transformed(const Matrix4& m) const {
		return Segment(a.transformed(m), b.transformed(m), color);
	}

	Segment clipped(double d) const {
		if (a.z <= -d && b.z <= -d) return Segment();
		if (a.z > -d && b.z > -d) return *this;

		double x, y, z;
		double coeff;

		if (a.z <= -d) {
			x = a.x - b.x;
			y = a.y - b.y;
			z = a.z - b.z;
			coeff = (-d - b.z) / z;

			return Segment(
				Point(b.x + coeff * x, b.y + coeff * y, -d),
				b,
				color
			);
		}
		if (b.z <= -d) {
			x = b.x - a.x;
			y = b.y - a.y;
			z = b.z - a.z;
			coeff = (-d - a.z) / z;

			return Segment(
				a,
				Point(a.x + coeff * x, a.y + coeff * y, -d),
				color
			);
		}

		return *this;
	}
};

struct Mesh {
	std::vector<Segment> segments;

	void addSegment(Segment s) {
		segments.push_back(s);
	}
};