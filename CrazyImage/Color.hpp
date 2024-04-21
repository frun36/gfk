class Color {
private:
	Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
public:	
	int r, g, b;

	Color() : r(0), g(0), b(0) {}

	static Color fromRGB(unsigned char r, unsigned char g, unsigned char b) {
		return Color(r, g, b);
	}

	Color operator+(const Color& other) const {
		Color c;
		c.r = r + other.r;
		c.g = g + other.g;
		c.b = b + other.b;
		return c;
	}

	Color operator-(const Color& other) const {
		Color c;
		c.r = r - other.r;
		c.g = g - other.g;
		c.b = b - other.b;
		return c;
	}

	Color normalized() const {
		Color c;
		c.r = r > 255 ? 255 : (r < 0 ? 0 : r);
		c.g = g > 255 ? 255 : (g < 0 ? 0 : g);
		c.b = b > 255 ? 255 : (b < 0 ? 0 : b);
		return c;
	}
};