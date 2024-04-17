#pragma once

#include <vector>

struct Point {
	double x, y, z;

	Point(double x, double y, double z) : x(x), y(y), z(z) {}
};

struct Color {
	char r, g, b;

	Color(char r, char g, char b) : r(r), g(g), b(b) {}
};

struct Segment {
	Point a, b;
	Color color;

	Segment(Point a, Point b, Color color) : a(a), b(b), color(color) {}
};

class Mesh {
private:
	std::vector<Segment> _data;
public:
	void addSegment(Segment s) {
		_data.push_back(s);
	}
};