#pragma once

#include <wx/wx.h>
#include "Config.hpp"
#include "Linalg.hpp"

class Plot {
private:
	const Config& _config;
	unsigned _voxelWidth;
public:
	Plot(const Config& config, unsigned voxelWidth) : _config(config), _voxelWidth(voxelWidth) {}

	void draw(wxDC& dc) const;

	static wxColour getVoxelColor(double z, bool color);

	static double getFunctionValue(double x, double y, const std::vector<std::array<double, 3>>& functionData);
};