#pragma warning(disable: 4996)

#include "Plot.hpp"
#include "Line.hpp"

void Plot::draw(wxDC& dc, int width, int height) {
	// Function + min/max values
	std::function<double(double)> f;
	switch (_config->getFunction()) {
	case 0:
		f = [](double x) { return x + sin(4 * x); };
		break;
	case 1:
		f = [](double x) { return x * x;  };
		break;
	case 2:
		f = [](double x) { return 0.5 * exp(4 * x - 3 * x * x); };
		break;
	default:
		f = [](double x) { return x; };
	}
	_yMin = f(_config->getXStart());
	_yMax = f(_config->getXStart());

	double step = (_config->getXEnd() - _config->getXStart()) / _xResolution;
	double x0, x1;

	for (size_t i = 0; i < _xResolution; i++) {
		x1 = _config->getXStart() + (i + 1) * step;

		if (f(x1) > _yMax) _yMax = f(x1);
		if (f(x1) < _yMin) _yMin = f(x1);
	}


	// Select rotation origin
	double xOrigin, yOrigin;
	if (_config->getRotationOrigin() == Config::Origin::WORLD) {
		xOrigin = abs(_config->getX0()) / (_config->getX1() - _config->getX0()) * width;
		yOrigin = abs(_config->getY0()) / (_config->getY1() - _config->getY0()) * height;
	}
	else {
		xOrigin = 0.5 * width;
		yOrigin = 0.5 * height;
	}


	// Coordinate conversion
	Matrix worldCoordinates = Matrix::identity()
		.coordinateChange(
			_config->getX0(),
			_config->getY0(),
			0,
			height,
			width / (_config->getX1() - _config->getX0()),
			-height / (_config->getY1() - _config->getY0())
		);


	// Transform of each line
	auto display = [&](Line line) {
		line
			.transform(worldCoordinates)
			.transform(Matrix::identity().translate(_config->getXTrans(), _config->getYTrans()))
			.transform(Matrix::identity().rotate(-_config->getAlpha()).fromOrigin(xOrigin + _config->getXTrans(), yOrigin + _config->getYTrans()))
			.draw(dc);
		};


	// X axis
	display(Line(_config->getXStart(), 0, _config->getXEnd(), 0));

	// X ticks
	double xTickStep = (_config->getXEnd() - _config->getXStart()) / 4;
	for (size_t i = 1; i < 4; i++)
		display(Line(_config->getXStart() + xTickStep * i, -0.05, _config->getXStart() + xTickStep * i, 0.05));

	// X Arrow
	display(Line(_config->getXEnd(), 0, _config->getXEnd() - 0.1, 0.05));
	display(Line(_config->getXEnd(), 0, _config->getXEnd() - 0.1, -0.05));


	// Y axis
	display(Line(0, _yMin, 0, _yMax));

	// Y ticks
	double yTickStep = (_yMax - _yMin) / 4;
	for (size_t i = 1; i < 4; i++)
		display(Line(-0.05, _yMin + yTickStep * i, 0.05, _yMin + yTickStep * i));

	// Y Arrow
	display(Line(0, _yMax, 0.05, _yMax - 0.1));
	display(Line(0, _yMax, -0.05, _yMax - 0.1));

	// Plot
	dc.SetPen(*wxBLUE_PEN);
	for (size_t i = 0; i < _xResolution; i++) {
		x0 = _config->getXStart() + i * step;
		x1 = x0 + step;
		display(Line(x0, f(x0), x1, f(x1)));
	}
}
