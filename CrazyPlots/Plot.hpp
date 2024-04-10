#ifndef PLOT_HPP
#define PLOT_HPP

#include "Config.hpp"
#include <memory>
#include <wx/wx.h>

#include "Linalg.hpp"

class Plot {
private:
    std::shared_ptr<Config> _config;
    size_t _xResolution = 128;  // number of segments in plot
    double _yMin = -1, _yMax = 1;

public:
    Plot(std::shared_ptr<Config> config) : _config(config) {}

    void draw(wxDC& dc, int width, int height);  // draws the plot

    double getYMin() const { return _yMin; }
    double getYMax() const { return _yMax; }
};

#endif