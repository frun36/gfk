#include "MainFrame.hpp"

void MainFrame::AddRow(wxBoxSizer* sizer, const wxString& label1,
	wxWindow* ctrl1, const wxString& label2, wxWindow* ctrl2) {
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(new wxStaticText(this, wxID_ANY, label1), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	hbox->Add(ctrl1, 1, wxEXPAND | wxALL, 5);
	if (ctrl2 != nullptr) {
		hbox->Add(new wxStaticText(this, wxID_ANY, label2), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
		hbox->Add(ctrl2, 1, wxEXPAND | wxALL, 5);
	}

	sizer->Add(hbox, 0, wxEXPAND);
}

void MainFrame::displayConfig() {
	_x0Control->SetValue(std::format("{:.2}", _config->getX0()));
	_y0Control->SetValue(std::format("{:.2}", _config->getY0()));
	_x1Control->SetValue(std::format("{:.2}", _config->getX1()));
	_y1Control->SetValue(std::format("{:.2}", _config->getY1()));

	_xTransControl->SetValue(std::format("{:.2}", _config->getXTrans()));
	_yTransControl->SetValue(std::format("{:.2}", _config->getYTrans()));

	_xStartControl->SetValue(std::format("{:.2}", _config->getXStart()));
	_xEndControl->SetValue(std::format("{:.2}", _config->getXEnd()));

	_rotationControl->SetScrollPos(1, static_cast<int>(_config->getAlpha()));
	_rotationLabel->SetLabelText(std::format("{:.2}", _config->getAlpha()));

	if (_config->getRotationOrigin() == Config::Origin::SCREEN) {
		_screenCenterControl->SetValue(true);
		_worldCenterControl->SetValue(false);
	}
	else {
		_screenCenterControl->SetValue(false);
		_worldCenterControl->SetValue(true);
	}

	_functionControl->SetSelection(_config->getFunction());

}

double MainFrame::stringToDouble(const wxString& str) {
	if (str.empty() || str == "-") {
		return 0.0;
	}
	
	double value;
	if (str.ToDouble(&value)) {
		return value;
	}
	else {
		return 0.0;
	}
}

void MainFrame::updateConfig() {
	// Text boxes
	_config->setX0(stringToDouble(_x0Control->GetValue()));
	_config->setY0(stringToDouble(_y0Control->GetValue()));
	_config->setX1(stringToDouble(_x1Control->GetValue()));
	_config->setY1(stringToDouble(_y1Control->GetValue()));

	_config->setXTrans(stringToDouble(_xTransControl->GetValue()));
	_config->setYTrans(stringToDouble(_yTransControl->GetValue()));

	_config->setXStart(stringToDouble(_xStartControl->GetValue()));
	_config->setXEnd(stringToDouble(_xEndControl->GetValue()));

	// Alpha
	_config->setAlpha(_rotationControl->GetThumbPosition());
	_rotationLabel->SetLabelText(std::format("{:.0f}", _config->getAlpha()));

	// Origin
	if (_screenCenterControl->GetValue()) {
		_config->setRotationOrigin(Config::Origin::SCREEN);
	}
	else {
		_config->setRotationOrigin(Config::Origin::WORLD);
	}

	// Function
	_config->setFunction(_functionControl->GetSelection());

	Refresh();
}

MainFrame::MainFrame(std::shared_ptr<Config> config)
	: wxFrame(NULL, wxID_ANY, "CrazyPlots"), _config(config) {
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetMinSize(wxSize(1500, 900));

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer(wxVERTICAL);

	_canvas = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	_canvas->SetForegroundColour(wxColour(0, 0, 0));
	_canvas->SetBackgroundColour(wxColour(255, 255, 255));

	panelSizer->Add(_canvas, 1, wxEXPAND | wxALL, 5);

	mainSizer->Add(panelSizer, 1, wxEXPAND, 5);

	wxBoxSizer* menuSizer;
	menuSizer = new wxBoxSizer(wxVERTICAL);

	// World Coordinates
	menuSizer->Add(new wxStaticText(this, wxID_ANY, "World coordinates"), 0, wxEXPAND | wxALL, 5);
	_x0Control = new wxTextCtrl(this, wxID_ANY);
	_x0Control->SetMaxSize(wxSize(100, -1));

	_y0Control = new wxTextCtrl(this, wxID_ANY);
	_y0Control->SetMaxSize(wxSize(100, -1));

	_x1Control = new wxTextCtrl(this, wxID_ANY);
	_x1Control->SetMaxSize(wxSize(100, -1));

	_y1Control = new wxTextCtrl(this, wxID_ANY);
	_y1Control->SetMaxSize(wxSize(100, -1));

	AddRow(menuSizer, "x0", _x0Control, "y0", _y0Control);
	AddRow(menuSizer, "x1", _x1Control, "y1", _y1Control);

	// Rotation
	_rotationControl = new wxScrollBar(this, wxID_ANY);
	_rotationControl->SetRange(360);

	_rotationLabel = new wxStaticText(this, wxID_ANY, "-");
	_rotationLabel->SetMaxSize(wxSize(100, -1));
	menuSizer->Add(new wxStaticText(this, wxID_ANY, "Rotation"), 0, wxEXPAND | wxALL, 5);
	AddRow(menuSizer, "alpha", _rotationControl, "", _rotationLabel);

	// Radio Buttons
	_screenCenterControl = new wxRadioButton(this, wxID_ANY, "Screen center");
	_worldCenterControl = new wxRadioButton(this, wxID_ANY, "World center");
	menuSizer->Add(_screenCenterControl, 0, wxEXPAND | wxALL, 5);
	menuSizer->Add(_worldCenterControl, 0, wxEXPAND | wxALL, 5);

	// Translation
	_xTransControl = new wxTextCtrl(this, wxID_ANY);
	_xTransControl->SetMaxSize(wxSize(100, -1));

	_yTransControl = new wxTextCtrl(this, wxID_ANY);
	_yTransControl->SetMaxSize(wxSize(100, -1));

	menuSizer->Add(new wxStaticText(this, wxID_ANY, "Translation"), 0, wxEXPAND | wxALL, 5);
	AddRow(menuSizer, "x", _xTransControl, "y", _yTransControl);

	// Limits
	_xStartControl = new wxTextCtrl(this, wxID_ANY);
	_xStartControl->SetMaxSize(wxSize(100, -1));

	_xEndControl = new wxTextCtrl(this, wxID_ANY);
	_xEndControl->SetMaxSize(wxSize(100, -1));

	menuSizer->Add(new wxStaticText(this, wxID_ANY, "Limits"), 0, wxEXPAND | wxALL, 5);
	AddRow(menuSizer, "x start", _xStartControl, "x stop", _xEndControl);
	// Assuming 'y min' and 'y max' are controlled by variables, otherwise use wxTextCtrl for user input.
	_yMinLabel = new wxStaticText(this, wxID_ANY, "-");
	_yMaxLabel = new wxStaticText(this, wxID_ANY, "-");
	AddRow(menuSizer, "y min", _yMinLabel, "y max", _yMaxLabel);

	// Dropdown menu
	wxString choices[] = { "x*sin(4x)", "x^2", "0.5*exp(4x-3x^2)" };
	_functionControl = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, WXSIZEOF(choices), choices);
	menuSizer->Add(_functionControl, 0, wxEXPAND | wxALL, 5);

	// Buttons
	_centerControl = new wxButton(this, wxID_ANY, "Center");
	_saveControl = new wxButton(this, wxID_ANY, "Save config");
	_loadControl = new wxButton(this, wxID_ANY, "Load config");
	menuSizer->Add(_centerControl, 0, wxALIGN_CENTER | wxALL, 5);
	AddRow(menuSizer, "", _saveControl, "", _loadControl);


	mainSizer->Add(menuSizer, 0, wxEXPAND, 5);

	this->SetSizer(mainSizer);
	this->Layout();
	this->Centre(wxBOTH);

	displayConfig();

	// Events
	_canvas->Bind(wxEVT_UPDATE_UI, [this](wxUpdateUIEvent& event) { repaint(); });

	_x0Control->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });
	_y0Control->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });
	_x1Control->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });
	_y1Control->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });
	_xTransControl->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });
	_yTransControl->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });
	_xStartControl->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });
	_xEndControl->Bind(wxEVT_TEXT, [this](wxCommandEvent&) { updateConfig(); });

	/*_rotationControl->Bind(wxEVT_SCROLL_TOP, [this](wxScrollEvent&) { updateConfig(); });
	_rotationControl->Bind(wxEVT_SCROLL_BOTTOM, [this](wxScrollEvent&) { updateConfig(); });
	_rotationControl->Bind(wxEVT_SCROLL_LINEUP, [this](wxScrollEvent&) { updateConfig(); });
	_rotationControl->Bind(wxEVT_SCROLL_LINEDOWN, [this](wxScrollEvent&) { updateConfig(); });
	_rotationControl->Bind(wxEVT_SCROLL_PAGEUP, [this](wxScrollEvent&) { updateConfig(); });
	_rotationControl->Bind(wxEVT_SCROLL_PAGEDOWN, [this](wxScrollEvent&) { updateConfig(); });
	_rotationControl->Bind(wxEVT_SCROLL_THUMBTRACK, [this](wxScrollEvent&) { updateConfig(); });
	_rotationControl->Bind(wxEVT_SCROLL_THUMBRELEASE, [this](wxScrollEvent&) { updateConfig(); });*/
	_rotationControl->Bind(wxEVT_SCROLL_CHANGED, [this](wxScrollEvent&) { updateConfig(); });

	_screenCenterControl->Bind(wxEVT_RADIOBUTTON, [this](wxCommandEvent&) { updateConfig(); });
	_worldCenterControl->Bind(wxEVT_RADIOBUTTON, [this](wxCommandEvent&) { updateConfig(); });
	_functionControl->Bind(wxEVT_CHOICE, [this](wxCommandEvent&) { updateConfig(); });
	_centerControl->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { 
		_x0Control->SetLabelText(_xStartControl->GetLineText(0));
		_x1Control->SetLabelText(_xEndControl->GetLineText(0));
		updateConfig(); 
	});
	_saveControl->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { updateConfig(); });
	_loadControl->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { updateConfig(); });



}


void MainFrame::repaint() {
	wxClientDC dc1(_canvas);
	wxBufferedDC dc(&dc1);

	dc.SetBrush(*wxWHITE_BRUSH);
	dc.Clear();

	Plot plt(_config);
	int w, h;
	_canvas->GetSize(&w, &h);
	plt.draw(dc, w, h);

	_yMinLabel->SetLabelText(std::format("{:.2}", plt.getYMin()));
	_yMaxLabel->SetLabelText(std::format("{:.2}", plt.getYMax()));
}