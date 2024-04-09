#ifndef LINALG_HPP
#define LINALG_HPP

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

	double getY(double y) const {
		return _data[1];
	}
};

class Matrix {
private:
	double _data[3][3];

public:
	Matrix() {
		_data[0][0] = 0.0; _data[0][1] = 0.0; _data[0][2] = 0.0;
		_data[1][0] = 0.0; _data[1][1] = 0.0; _data[1][2] = 0.0;
		_data[2][0] = 0.0; _data[2][1] = 0.0; _data[2][2] = 1.0;
	}

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
};

#endif