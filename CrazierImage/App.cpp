#include <wx/wx.h>

#include "MainFrame.hpp"
#include "FreeImagePlus.h"

class App : public wxApp {
public:
	bool OnInit() {
		FreeImage_Initialise();
		wxInitAllImageHandlers();

		SetProcessDPIAware();
		MainFrame* frame = new MainFrame();

		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP(App);