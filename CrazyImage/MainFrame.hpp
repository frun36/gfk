#pragma once

#include <wx/wx.h>
#include "Config.hpp"

class MainFrame : public wxFrame {
private:
	Config _config;
	wxScrolledWindow* _canvas;

	wxButton* _buttonDefault,
		* _buttonGrayscale, * _buttonBlur,
		* _buttonMirror, * _buttonReplace,
		* _buttonRescale, * _buttonRotate,
		* _buttonRotateHue, * _buttonMask,
		* _buttonPrewitt, * _buttonThresh;

	wxSlider* _sliderBrightness, * _sliderContrast;

public:
	MainFrame();
};

