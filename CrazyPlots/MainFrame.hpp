#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
	MainFrame() : wxFrame(NULL, wxID_ANY, "CrazyPlots") {
	
	}
};

#endif // !MAIN_FRAME_HPP
