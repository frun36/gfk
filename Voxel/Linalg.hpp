#pragma once

#include <cmath>

class Matrix;

class Vector {
	friend Matrix;
private:
	double _data[3];
public:
	Vector(double x = 0.0, double y = 0.0) {
		_data[0] = x;
		_data[1] = y;
		_data[2] = 1.0;
	}

	void setX(double x) {
		_data[0] = x;
	}

	void setY(double y) {
		_data[1] = y;
	}

	double getX() const {
		return _data[0];
	}

	double getY() const {
		return _data[1];
	}
};

class Matrix {
private:
	double _data[3][3];

	Matrix() {
		_data[0][0] = 1.0; _data[0][1] = 0.0; _data[0][2] = 0.0;
		_data[1][0] = 0.0; _data[1][1] = 1.0; _data[1][2] = 0.0;
		_data[2][0] = 0.0; _data[2][1] = 0.0; _data[2][2] = 1.0;
	}

public:
	Matrix operator*(const Matrix& other) const {
		int i, j, k;
		Matrix tmp;

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				tmp._data[i][j] = 0.0;

				for (k = 0; k < 3; k++)
					tmp._data[i][j] = tmp._data[i][j] + (_data[i][k] * other._data[k][j]);
			}
		}

		return tmp;
	}

	Vector operator*(const Vector& v) const {
		unsigned int i, j;
		Vector tmp;

		for (i = 0; i < 3; i++) {
			tmp._data[i] = 0.0;
			for (j = 0; j < 3; j++) tmp._data[i] = tmp._data[i] + (_data[i][j] * v._data[j]);
		}
		return tmp;
	}

	static Matrix identity() {
		return Matrix();
	}

	Matrix coordinateChange(double x0World, double y0World,
		double x0Screen, double y0Screen,
		double xScale, double yScale) const {
		Matrix m;
		m._data[0][0] = xScale;	m._data[0][1] = 0.0;	m._data[0][2] = x0Screen - xScale * x0World;
		m._data[1][0] = 0.0;	m._data[1][1] = yScale;	m._data[1][2] = y0Screen - yScale * y0World;
		m._data[2][0] = 0.0;	m._data[2][1] = 0.0;	m._data[2][2] = 1.0;

		return m * *this;
	}

	Matrix scale(double xScale, double yScale) const {
		Matrix m;
		m._data[0][0] = xScale;	m._data[0][1] = 0.0;	m._data[0][2] = 0.0;
		m._data[1][0] = 0.0;	m._data[1][1] = yScale;	m._data[1][2] = 0.0;
		m._data[2][0] = 0.0;	m._data[2][1] = 0.0;	m._data[2][2] = 1.0;

		return m * *this;
	}

	Matrix translate(double x, double y) const {
		Matrix m;
		m._data[0][0] = 1.0;	m._data[0][1] = 0.0;	m._data[0][2] = x;
		m._data[1][0] = 0.0;	m._data[1][1] = 1.0;	m._data[1][2] = y;
		m._data[2][0] = 0.0;	m._data[2][1] = 0.0;	m._data[2][2] = 1.0;

		return m * *this;
	}

	Matrix rotate(double degrees) const {
		double radians = degrees * M_PI / 180.0;

		Matrix m;
		m._data[0][0] = cos(radians);	m._data[0][1] = -sin(radians);	m._data[0][2] = 0.0;
		m._data[1][0] = sin(radians);	m._data[1][1] = cos(radians);	m._data[1][2] = 0.0;
		m._data[2][0] = 0.0;			m._data[2][1] = 0.0;			m._data[2][2] = 1.0;

		return m * *this;
	}

	Matrix shear(double x, double y) const {
		Matrix m;
		m._data[0][0] = 1.0;	m._data[0][1] = x;		m._data[0][2] = 0.0;
		m._data[1][0] = y;		m._data[1][1] = 1.0;	m._data[1][2] = 0.0;
		m._data[2][0] = 0.0;	m._data[2][1] = 0.0;	m._data[2][2] = 1.0;

		return m * *this;
	}

	Matrix fromOrigin(double x, double y) const {
		Matrix translate = Matrix::identity().translate(-x, -y);
		Matrix translateBack = Matrix::identity().translate(x, y);

		return translateBack * *this * translate;
	}
};