#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <wx/wx.h>
#include <memory>

#include "Config.hpp"

class MainFrame : public wxFrame {
private:
	std::shared_ptr<Config> _config;
	wxPanel* _canvas;
	wxTextCtrl* _x0Control, * _y0Control, * _x1Control, * _y1Control, * _xTransControl, * _yTransControl, * _xStartControl, * _xEndControl;
	wxScrollBar* _rotationControl;
	wxRadioButton* _screenCenterControl, * _worldCenterControl;
	wxChoice* _functionControl;
	wxButton* _saveControl, * _loadControl, * _centerControl;
	wxStaticText* _yMinLabel, * _yMaxLabel, * _rotationLabel;

	void AddRow(wxBoxSizer* sizer,
		const wxString& label1, wxWindow* ctrl1,
		const wxString& label2 = "", wxWindow* ctrl2 = nullptr);

public:
	MainFrame(std::shared_ptr<Config> config);
};

#endif // !MAIN_FRAME_HPP
