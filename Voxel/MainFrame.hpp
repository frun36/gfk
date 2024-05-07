#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame {
private:
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

	std::function<double(double, double)> _function;
	int _rotation = 0;
	int _tilt = 50;
	bool _color = false;
public:
	MainFrame();
};
