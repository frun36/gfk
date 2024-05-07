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
};