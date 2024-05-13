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

	wxImage _imgOrg, _imgMod;

	void _repaint();

	void _loadImage();
	void _handleExif(const wxString& name);
public:
	MainFrame();
};
