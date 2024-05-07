#include "Plot.hpp"

void Plot::draw(wxDC& dc) const {
	auto plotTransform = Matrix::identity()
		.translate(-250, -250)
		.scale(0.75, 0.75)
		.shear(-0.1, 0)
		.scale(1, (50 + _config.getTilt()) / 200.)
		.translate(250, 300);

	auto coordinateTransform = Matrix::identity()
		.translate(-250, -250)
		.scale(0.01, 0.01)
		.rotate(_config.getRotation());

	dc.SetBrush(*wxWHITE_BRUSH);
	dc.Clear();
	dc.SetPen(*wxTRANSPARENT_PEN);

	std::vector<std::array<double, 3>> grid;
	double min = INFINITY;
	double max = -INFINITY;

	for (int x = 0; x < 500; x += _voxelWidth) {
		for (int y = 0; y < 500; y += _voxelWidth) {
			auto pFunction = coordinateTransform * Vector(x, y);
			double z = getFunctionValue(pFunction.getX(), pFunction.getY(), _config.getFunctionData());
			min = std::min(min, z);
			max = std::max(max, z);
			grid.push_back({ static_cast<double>(x), static_cast<double>(y), z });
		}
	}

	for (auto& p : grid) {
		auto pVoxel = plotTransform * Vector(p[0], p[1]);
		double z = p[2];
		z = (z - min) / (max - min);
		wxBrush b;
		b.SetColour(getVoxelColor(z, _config.getColor()));
		dc.SetBrush(b);
		dc.DrawRectangle(pVoxel.getX(), pVoxel.getY(), _voxelWidth, std::min(-5., -50 * z));
	}
}

wxColour Plot::getVoxelColor(double z, bool color) {

	return
		color ?
		heatmap(z) :
		wxColour(255 * z, 255 * z, 255 * z);
}

double Plot::getFunctionValue(double x, double y, const std::vector<std::array<double, 3>>& functionData) {
	// Shepard's method
	double numerator = 0, denominator = 0;
	double x_k, y_k, z_k, w_k;
	for (auto& data : functionData) {
		x_k = data[0];
		y_k = data[1];
		z_k = data[2];
		if (x_k == x && y_k == y)
			return z_k;

		w_k = 1. / ((x - x_k) * (x - x_k) + (y - y_k) * (y - y_k));

		numerator += w_k * z_k;
		denominator += w_k;
	}
	return numerator / denominator;
}

wxColour Plot::heatmap(double val) {
	constexpr int NUM_COLORS = 4;
	const double positions[NUM_COLORS] = { 0.0, 0.25, 0.75, 1.0 };
	const int red[NUM_COLORS] = { 0, 0, 255, 255 };
	const int green[NUM_COLORS] = { 0, 255, 255, 0 };
	const int blue[NUM_COLORS] = { 255, 255, 0, 0 };

	int index = 0;
	while (index < NUM_COLORS - 1 && val > positions[index + 1]) {
		index++;
	}

	double fraction = (val - positions[index]) / (positions[index + 1] - positions[index]);
	int r = red[index] + static_cast<int>(fraction * (red[index + 1] - red[index]));
	int g = green[index] + static_cast<int>(fraction * (green[index + 1] - green[index]));
	int b = blue[index] + static_cast<int>(fraction * (blue[index + 1] - blue[index]));

	return wxColour(r, g, b);
}
