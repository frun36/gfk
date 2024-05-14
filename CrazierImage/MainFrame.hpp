#pragma once

#include <wx/wx.h>
#include <array>

#include "CImg.h"

class MainFrame : public wxFrame {
private:
	wxPanel* _canvas;
	wxButton* _bLoad;
	wxButton* _bCensor;
	wxButton* _bErode;
	wxCheckBox* _cbAnimate;
	wxGauge* _gAnimation;
	wxTextCtrl* _teExif;

	wxImage _imgOrg, _imgMod;

	std::array<wxImage, 60> _frames;
	size_t _currFrame = 0;

	void _repaint();

	void _loadImage();
	void _handleExif(const wxString& name);
	static cimg_library::CImg<unsigned char> wxImageAsCImg(const wxImage& img);
	static wxImage cImgAsWxImage(const cimg_library::CImg<unsigned char>& img);
public:
	MainFrame();
};
