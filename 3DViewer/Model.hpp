#pragma once

#include <wx/wx.h>

#include "Geometry.hpp"
#include "Config.hpp"

#include <memory>

class Model {
private:
	const Config& _config;
	Mesh _mesh;
public:
	Model(const Config& config) : _config(config) {}

	void setMesh(Mesh&& mesh) { _mesh = mesh; }

	void draw(wxDC& dc, int width, int height) const;
};

