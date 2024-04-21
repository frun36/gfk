class Color {
private:
	Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

	static Color _hueToRGB(float h, float c, float x, float m) {
		float r, g, b;
		if (h < 60.f) {
			r = c;
			g = x;
			b = 0;
		}
		else if (h < 120.f) {
			r = x;
			g = c;
			b = 0;
		}
		else if (h < 180.f) {
			r = 0;
			g = c;
			b = x;
		}
		else if (h < 240.f) {
			r = 0;
			g = x;
			b = c;
		}
		else if (h < 300.f) {
			r = x;
			g = 0;
			b = c;
		}
		else {
			r = c;
			g = 0;
			b = x;
		}

		return Color(255. * (r + m), 255. * (g + m), 255. * (b + m));
	}

public:	
	int r, g, b;

	Color() : r(0), g(0), b(0) {}

	static Color fromRGB(unsigned char r, unsigned char g, unsigned char b) {
		return Color(r, g, b);
	}

	static Color fromHSL(float h, float s, float l) {
		h = h * 360.f;

		float c = (1 - fabs(2 * l - 1)) * s;
		float x = c * (1 - fabs(fmodf(h / 60.f, 2.f) - 1));

		float m = l - c / 2;

		return _hueToRGB(h, c, x, m);
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

	//float getH() const {
	//	float rNormalized = static_cast<float>(r) / 255.;
	//	float gNormalized = static_cast<float>(g) / 255.;
	//	float bNormalized = static_cast<float>(b) / 255.;

	//	float cMax = std::max({ rNormalized, gNormalized, bNormalized });
	//	float cMin = std::min({ rNormalized, gNormalized, bNormalized });
	//	float delta = cMax - cMin;

	//	if (delta == 0) return 0;

	//	float hue = 0;

	//	if (cMax == rNormalized) {
	//		hue = ((gNormalized - bNormalized) / 6) / delta;
	//		//hue = 0;
	//	}
	//	else if (cMax == gNormalized) {
	//		hue = (1.0f / 3) + ((bNormalized - rNormalized) / 6) / delta;
	//		//hue = 1.f / 3;
	//	}
	//	else if (cMax == bNormalized) {
	//		hue =  (2.0f / 3) + ((rNormalized - gNormalized) / 6) / delta;
	//		//hue = 2.f / 3;
	//	}
	//	if (hue < 0)
	//		hue += 1;
	//	if (hue > 1)
	//		hue -= 1;

	//	return hue;
	//}

	//float getS() const {
	//	float rNormalized = static_cast<float>(r) / 255;
	//	float gNormalized = static_cast<float>(g) / 255;
	//	float bNormalized = static_cast<float>(b) / 255;

	//	float cMax = std::max({ rNormalized, gNormalized, bNormalized });
	//	float cMin = std::min({ rNormalized, gNormalized, bNormalized });
	//	float delta = cMax - cMin;

	//	return cMax + cMin == 0 || cMax + cMin == 2 ? 0 : delta / (1 - fabs(cMax + cMin - 1));
	//}

	//float getL() const {
	//	float rNormalized = static_cast<float>(r) / 255;
	//	float gNormalized = static_cast<float>(g) / 255;
	//	float bNormalized = static_cast<float>(b) / 255;

	//	float cMax = std::max({ rNormalized, gNormalized, bNormalized });
	//	float cMin = std::min({ rNormalized, gNormalized, bNormalized });
	//	float delta = cMax - cMin;

	//	return (cMax + cMin) / 2;
	//}
};