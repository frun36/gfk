#pragma once

class Vector4;

class Matrix4 {
private:
	Matrix4() {};
	double _data[4][4] = {};
public:
	Matrix4 operator*(const Matrix4& other);
	Vector4 operator*(const Vector4& v);
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

	double SetX(double x) { _data[0] = x; }
	double SetY(double y) { _data[1] = y; }
	double SetZ(double z) { _data[2] = z; }
	
	double GetX() const { return _data[0]; }
	double GetY() const { return _data[1]; }
	double GetZ() const { return _data[2]; }
	
	Vector4 operator-(const Vector4& other);
	friend Vector4 operator*(double a, const Vector4& v);
};
