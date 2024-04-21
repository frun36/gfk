#pragma once

#include <wx/wx.h>
#include "Color.hpp"

class MainFrame : public wxFrame {
private:
	wxScrolledWindow* _canvas;

	wxButton* _buttonDefault,
		* _buttonGrayscale, * _buttonBlur,
		* _buttonMirror, * _buttonReplace,
		* _buttonRescale, * _buttonRotate,
		* _buttonRotateHue, * _buttonMask,
		* _buttonPrewitt, * _buttonThresh;

	wxSlider* _sliderBrightness, * _sliderContrast;

	void _repaint();

	static wxImage _brightness(wxImage& img, float brightness);
	static wxImage _contrast(wxImage& img, int contrast);

	static wxImage _prewitt(wxImage& img);
	static wxImage _thresh(wxImage& img, unsigned char thresh);

	static Color _applyVerticalMask(Color mask[3][3]);

public:
	wxImage imgOrg, imgMod, imgMask;

	MainFrame();
};

