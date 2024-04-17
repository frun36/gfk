#pragma once

class Config {
private:
	double _transX = 0, _transY = 0, _transZ = 0;
	double _rotX = 0, _rotY = 0, _rotZ = 0;
	double _scaleX = 1, _scaleY = 1, _scaleZ = 1;
public:
	// Setters for translation variables
	void setTransX(double transX) { _transX = transX; }
	void setTransY(double transY) { _transY = transY; }
	void setTransZ(double transZ) { _transZ = transZ; }

	// Setters for rotation variables
	void setRotX(double rotX) { _rotX = rotX; }
	void setRotY(double rotY) { _rotY = rotY; }
	void setRotZ(double rotZ) { _rotZ = rotZ; }

	// Setters for scale variables
	void setScaleX(double scaleX) { _scaleX = scaleX; }
	void setScaleY(double scaleY) { _scaleY = scaleY; }
	void setScaleZ(double scaleZ) { _scaleZ = scaleZ; }

	// Getters for translation variables
	double getTransX() const { return _transX; }
	double getTransY() const { return _transY; }
	double getTransZ() const { return _transZ; }

	// Getters for rotation variables
	double getRotX() const { return _rotX; }
	double getRotY() const { return _rotY; }
	double getRotZ() const { return _rotZ; }

	// Getters for scale variables
	double getScaleX() const { return _scaleX; }
	double getScaleY() const { return _scaleY; }
	double getScaleZ() const { return _scaleZ; }

	void reset() {
		_transX = 0; _transY = 0; _transZ = 0;
		_rotX = 0; _rotY = 0; _rotZ = 0;
		_scaleX = 1; _scaleY = 1; _scaleZ = 1;
	}
};

