#include <wx/wx.h>

#include "MainFrame.hpp"

class App : public wxApp
{
public:
	bool OnInit() {
		SetProcessDPIAware();
		MainFrame* frame = new MainFrame();
		frame->Show(true);
		return true;
	}
};

wxIMPLEMENT_APP(App);