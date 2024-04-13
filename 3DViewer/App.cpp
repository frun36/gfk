#include <wx/wx.h>

#include "MainFrame.hpp"

#include <memory>

class App : public wxApp {
public:
	bool OnInit() {
		SetProcessDPIAware();
		MainFrame* frame = new MainFrame();
		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP(App);