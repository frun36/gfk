#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame {
private:
	wxScrolledWindow* _canvas;

	wxButton* _buttonDefault,
		* _buttonGrayscale, * _buttonBlur,
		* _buttonMirror, * _buttonReplace,
		* _buttonRescale, * _buttonRotate,
		* _buttonRotateHue, * _buttonMask,
		* _buttonPrewitt, * _buttonThresh,
		* _buttonExtra;

	wxSlider* _sliderBrightness, * _sliderContrast;

	void _repaint();

	static wxImage _brightness(wxImage& img, int brightness);
	static wxImage _contrast(wxImage& img, int contrast);

	static wxImage _prewitt(wxImage& img);
	static wxImage _thresh(wxImage& img, unsigned char thresh);

public:
	wxImage imgOrg, imgMod, imgMask;

	MainFrame();
};

