#include <wx/wx.h>

#include "MainFrame.hpp"
class App : public wxApp {
public:
	bool OnInit() {
		SetProcessDPIAware();
		MainFrame* frame = new MainFrame();

		wxImage::AddHandler(new wxJPEGHandler);
		wxImage::AddHandler(new wxPNGHandler);
		wxImage image;

		wxLogNull logNo;
		if (!image.LoadFile("img.jpg")) {
			wxMessageBox(_("Failed to load image"));
			frame->Destroy();
			return true;
		}
		frame->imgOrg = image.Copy();
		frame->imgMod = frame->imgOrg.Copy();

		if (!image.LoadFile("mask.png")) {
			wxMessageBox(_("Failed to load mask"));
			frame->Destroy();
			return true;
		}
		frame->imgMask = image.Copy();

		frame->Show(true);
		SetTopWindow(frame);
		return true;
	}
};

wxIMPLEMENT_APP(App);