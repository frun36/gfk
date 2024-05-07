#include <wx/wx.h>

#include "MainFrame.hpp"

class App : public wxApp {
public:
	bool OnInit() {
		srand(376257);

		SetProcessDPIAware();
		MainFrame* frame = new MainFrame();

		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP(App);