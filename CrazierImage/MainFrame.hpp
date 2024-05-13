#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame {
private:
	wxPanel* _canvas;
	wxButton* _bLoad;
	wxButton* _bCensor;
	wxButton* _bErode;
	wxCheckBox* _cbAnimate;
	wxTextCtrl* _teExif;

	void _repaint();
public:
	MainFrame();
};
