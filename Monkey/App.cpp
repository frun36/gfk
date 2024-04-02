#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif // !WX_PRECOMP


#include "MonkeyMainFrame.h"

class App : public wxApp
{
public:
	bool OnInit();
};

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	SetProcessDPIAware();
	MonkeyMainFrame* frame = new MonkeyMainFrame(nullptr);
	frame->Show(true);
	return true;
}