#pragma once

class Vector4;

class Matrix4 {
private:
	Matrix4() {};
	double _data[4][4] = {};
public:
	Matrix4 operator*(const Matrix4& other) const;
	Vector4 operator*(const Vector4& v) const;
	static Matrix4 identity();

	Matrix4 translate(double x, double y, double z) const;
	Matrix4 rotateX(double theta) const;
	Matrix4 rotateY(double theta) const;
	Matrix4 rotateZ(double theta) const;
	Matrix4 scale(double x, double y, double z) const;
};

class Vector4 {
	friend Matrix4;
private:
	double _data[4];
public:
	Vector4(double x = 0, double y = 0, double z = 0);

	double setX(double x) { _data[0] = x; }
	double setY(double y) { _data[1] = y; }
	double setZ(double z) { _data[2] = z; }
	
	double getX() const { return _data[0]; }
	double getY() const { return _data[1]; }
	double getZ() const { return _data[2]; }

	Vector4 projected(double d) const;
};
