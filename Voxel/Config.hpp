#pragma once

#include <functional>

class Config {
private:
	std::function<double(double, double)> _function;
	int _rotation = 0;
	int _tilt = 50;
	bool _color = false;
public:
	std::function<double(double, double)> getFunction() const {
		return _function;
	}

	void setFunction(const std::function<double(double, double)>& function) {
		_function = function;
	}

	int getRotation() const {
		return _rotation;
	}

	void setRotation(int rotation) {
		_rotation = rotation;
	}

	int getTilt() const {
		return _tilt;
	}

	void setTilt(int tilt) {
		_tilt = tilt;
	}

	bool getColor() const {
		return _color;
	}
	void setColor(bool color) {
		_color = color;
	}
};