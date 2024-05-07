#pragma once

#include <functional>
#include <vector>
#include <array>

enum class Function { F1, F2, F3, F4 };

class Config {
private:
	Function _function = Function::F1;
	int _rotation = 0;
	int _tilt = 50;
	bool _color = false;
	std::vector<std::array<double, 3>> _functionData;

	void _prepareFunctionData();
public:
	Config(Function function, int rotation = 0, int tilt = 50, bool color = false)
		: _function(function), _rotation(rotation), _tilt(tilt), _color(color) {
		_prepareFunctionData();
	}

	const std::vector<std::array<double, 3>>& getFunctionData() const {
		return _functionData;
	}

	void setFunction(Function function) {
		_function = function;
		_prepareFunctionData();
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