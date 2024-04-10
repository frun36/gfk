#include "Config.hpp"

#include <fstream>

void Config::save(std::string filename) const {
    std::fstream f;

    f.open(filename, std::ios::out);
    f << _x0 << " " << _y0 << " " << _x1 << " " << _y1 << '\n';
    f << _alpha << '\n';
    f << static_cast<int>(_rotationOrigin) << '\n';
    f << _xTrans << " " << _yTrans << '\n';
    f << _xStart << " " << _xEnd << '\n';
    f << _function << '\n';
    f.close();
}

static std::istream& rd2EOL(std::istream& str) {
    int ch;

    while ((ch = str.get()) != EOF && ch != '\n');
    return str;
}

void Config::load(std::string filename) {
    std::fstream f;

    f.open(filename, std::ios::in);
    f >> _x0 >> _y0 >> _x1 >> _y1 >> rd2EOL;
    f >> _alpha >> rd2EOL;
    int origin;
    f >> origin >> rd2EOL;
    _rotationOrigin = static_cast<Origin>(origin);
    f >> _xTrans >> _yTrans >> rd2EOL;
    f >> _xStart >> _xEnd >> rd2EOL;
    f >> _function >> rd2EOL;
    f.close();
}