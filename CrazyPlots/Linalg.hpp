#ifndef LINALG_HPP
#define LINALG_HPP

class Matrix;

class Vector {
	friend Matrix;
private:
	double data[3];
public:
	Vector(double x = 0.0, double y = 0.0) {
		data[0] = x;
		data[1] = y;
		data[2] = 1.0;
	}

	void setX(double x) { data[0] = x; }

	void setY(double y) { data[1] = y; }

	double getX() const { return data[0]; }

	double getY(double y) const { return data[1]; }
};

class Matrix {
private:
	double data[3][3];

public:
	Matrix() {
		data[0][0] = 0.0; data[0][1] = 0.0; data[0][2] = 0.0;
		data[1][0] = 0.0; data[1][1] = 0.0; data[1][2] = 0.0;
		data[2][0] = 0.0; data[2][1] = 0.0; data[2][2] = 1.0;
	}

	Matrix operator*(const Matrix& other) const {
		int i, j, k;
		Matrix tmp;

		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
			{
				tmp.data[i][j] = 0.0;
				for (k = 0; k < 3; k++)
					tmp.data[i][j] = tmp.data[i][j] + (data[i][k] * other.data[k][j]);
			}
		return tmp;
	}

	Vector operator*(const Vector& v) const {
		unsigned int i, j;
		Vector tmp;

		for (i = 0; i < 3; i++)
		{
			tmp.data[i] = 0.0;
			for (j = 0; j < 3; j++) tmp.data[i] = tmp.data[i] + (data[i][j] * v.data[j]);
		}
		return tmp;
	}
};

#endif