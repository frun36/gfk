#include <wx/wx.h>

#include "MainFrame.hpp"
#include "Config.hpp"

#include <memory>

class App : public wxApp {
public:
	bool OnInit() {
		auto config = std::make_shared<Config>();

		SetProcessDPIAware();
		MainFrame* frame = new MainFrame(config);
		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP(App);