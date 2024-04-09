#ifndef PLOT_HPP
#define PLOT_HPP

#include "Config.hpp"
#include <memory>
#include <wx/wx.h>

#include "Linalg.hpp"

class Plot {
private:
    std::shared_ptr<Config> _config;
    size_t xResolution;  // number of segments in plot
    double x_min, x_max; // range of x values
    double y_min, y_max; // range of y values

public:
    Plot(std::shared_ptr<Config> config) : _config(config) {}

    void draw(wxDC& dc, int width, int height);  // draws the plot
};

#endif