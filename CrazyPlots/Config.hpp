#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config {
public:
	enum class Origin { WORLD, SCREEN };
private:
	double _x0, _y0, _x1, _y1;	// world rectangle coordinates
	double _alpha;				// plot rotation angle
	enum class Origin _rotationOrigin;
	double _xTrans, _yTrans;	// translation relative to the screen center
	double _xStart, _xEnd;		// x values
	int _function;				// selected function
public:
	Config();
	
	double getXStart() const { return _xStart; }
	void setXStart(double x) { _xStart = x; }
	
	double getXEnd() const { return _xEnd; }
	void setXEnd(double x) { _xEnd = x; }

	Origin getRotationOrigin() const { return _rotationOrigin; }
	void setRotationOrigin(Origin origin) { _rotationOrigin = origin; }

	double getAlpha() const { return _alpha; }
	void setAlpha(double alpha) { _alpha = alpha; }

	double getXTrans() const { return _xTrans; }
	void setXTrans(double x) { _xTrans = x; }

	double getYTrans() const { return _yTrans; }
	void setYTrans(double y) { _yTrans = y; }

	double getX0() const { return _x0; }
	void setX0(double x) { _x0 = x; }

	double getY0() const { return _y0; }
	void setY0(double y) { _y0 = y; }

	double getX1() const { return _x1; }
	void setX1(double x) { _x1 = x; }

	double getY1() const { return _y1; }
	void setY1(float v) { _y1 = v; }

	int getFunction() const { return _function; }
	void setFunction(int function) { _function = function; }

	void save(std::string filename);
	void load(std::string filename);
};

#endif // !CONFIG_HPP
