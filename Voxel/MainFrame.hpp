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
public:
	MainFrame();
};
