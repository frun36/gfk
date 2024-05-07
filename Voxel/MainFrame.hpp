#pragma once

#include <wx/wx.h>
#include "Config.hpp"

class MainFrame : public wxFrame {
private:
	Config _config;

	wxPanel* _canvas;
	wxButton* _button1;
	wxButton* _button2;
	wxButton* _button3;
	wxButton* _button4;
	wxStaticText* _stRotation;
	wxCheckBox* _cbColor;
	wxSlider* _sRotation;
	wxSlider* _sTilt;

	void _repaint();
public:
	MainFrame();
};
