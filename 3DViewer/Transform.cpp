#include "Transform.hpp"

#include <cmath>

Vector4::Vector4(double x, double y, double z) {
	_data[0] = x; _data[1] = y; _data[2] = z; _data[3] = 1.0;
}

Vector4 Vector4::projected(double d) const {
	/*return Vector4(
		_data[0] * d / _data[2],
		_data[1] * d / _data[2],
		d
	);*/

	return Vector4(
		_data[0] * 500,
		_data[1] * 500,
		0
	);
}

Matrix4 Matrix4::operator*(const Matrix4& m) const {
	int i, j, k;
	Matrix4 tmp;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tmp._data[i][j] = 0.0;
			for (k = 0; k < 4; k++)
				tmp._data[i][j] = tmp._data[i][j] + (_data[i][k] * m._data[k][j]);
		}
	}
	return tmp;
}

Matrix4 Matrix4::identity() {
	Matrix4 m;

	m._data[0][0] = 1.0;	m._data[0][1] = 0.0;	m._data[0][2] = 0.0;	m._data[0][3] = 0.0;
	m._data[1][0] = 0.0;	m._data[1][1] = 1.0;	m._data[1][2] = 0.0;	m._data[1][3] = 0.0;
	m._data[2][0] = 0.0;	m._data[2][1] = 0.0;	m._data[2][2] = 1.0;	m._data[2][3] = 0.0;
	m._data[3][0] = 0.0;	m._data[3][1] = 0.0;	m._data[3][2] = 0.0;	m._data[3][3] = 1.0;

	return m;
}

Matrix4 Matrix4::translate(double x, double y, double z) const {
	Matrix4 m;

	m._data[0][0] = 1.0;	m._data[0][1] = 0.0;	m._data[0][2] = 0.0;	m._data[0][3] = x;
	m._data[1][0] = 0.0;	m._data[1][1] = 1.0;	m._data[1][2] = 0.0;	m._data[1][3] = y;
	m._data[2][0] = 0.0;	m._data[2][1] = 0.0;	m._data[2][2] = 1.0;	m._data[2][3] = z;
	m._data[3][0] = 0.0;	m._data[3][1] = 0.0;	m._data[3][2] = 0.0;	m._data[3][3] = 1.0;

	return m * *this;
}

Matrix4 Matrix4::rotateX(double theta) const {
	Matrix4 m;

	m._data[0][0] = 1.0;	m._data[0][1] = 0.0;		m._data[0][2] = 0.0;			m._data[0][3] = 0.0;
	m._data[1][0] = 0.0;	m._data[1][1] = cos(theta);	m._data[1][2] = -sin(theta);	m._data[1][3] = 0.0;
	m._data[2][0] = 0.0;	m._data[2][1] = sin(theta);	m._data[2][2] = cos(theta);		m._data[2][3] = 0.0;
	m._data[3][0] = 0.0;	m._data[3][1] = 0.0;		m._data[3][2] = 0.0;			m._data[3][3] = 1.0;

	return m * *this;
}

Matrix4 Matrix4::rotateY(double theta) const {
	Matrix4 m;

	m._data[0][0] = cos(theta);		m._data[0][1] = 0.0;	m._data[0][2] = sin(theta);	m._data[0][3] = 0.0;
	m._data[1][0] = 0.0;			m._data[1][1] = 1.0;	m._data[1][2] = 0.0;		m._data[1][3] = 0.0;
	m._data[2][0] = -sin(theta);	m._data[2][1] = 0.0;	m._data[2][2] = cos(theta);	m._data[2][3] = 0.0;
	m._data[3][0] = 0.0;			m._data[3][1] = 0.0;	m._data[3][2] = 0.0;		m._data[3][3] = 1.0;

	return m * *this;
}

Matrix4 Matrix4::rotateZ(double theta) const {
	Matrix4 m;

	m._data[0][0] = cos(theta);	m._data[0][1] = -sin(theta);	m._data[0][2] = 0.0;	m._data[0][3] = 0.0;
	m._data[1][0] = sin(theta);	m._data[1][1] = cos(theta);		m._data[1][2] = 0.0;	m._data[1][3] = 0.0;
	m._data[2][0] = 0.0;		m._data[2][1] = 0.0;			m._data[2][2] = 1.0;	m._data[2][3] = 0.0;
	m._data[3][0] = 0.0;		m._data[3][1] = 0.0;			m._data[3][2] = 0.0;	m._data[3][3] = 1.0;

	return m * *this;
}

Matrix4 Matrix4::scale(double x, double y, double z) const {
	Matrix4 m;

	m._data[0][0] = x;		m._data[0][1] = 0.0;	m._data[0][2] = 0.0;	m._data[0][3] = 0.0;
	m._data[1][0] = 0.0;	m._data[1][1] = y;		m._data[1][2] = 0.0;	m._data[1][3] = 0.0;
	m._data[2][0] = 0.0;	m._data[2][1] = 0.0;	m._data[2][2] = z;		m._data[2][3] = 0.0;
	m._data[3][0] = 0.0;	m._data[3][1] = 0.0;	m._data[3][2] = 0.0;	m._data[3][3] = 1.0;

	return m * *this;
}

Vector4 Matrix4::operator*(const Vector4& v) const {
	unsigned int i, j;
	Vector4 tmp;

	for (i = 0; i < 4; i++) {
		tmp._data[i] = 0.0;
		for (j = 0; j < 4; j++)
			tmp._data[i] = tmp._data[i] + (_data[i][j] * v._data[j]);
	}

	return tmp;
}
