#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <wx/wx.h>

class MainFrame : public wxFrame {
private:
	wxPanel* _canvas;
	wxTextCtrl* _x0Control, * _y0Control, * _x1Control, * _y1Control, * _xTransControl, * _yTransControl, * _xStartControl, * _xEndControl;
	wxScrollBar* _rotationControl;
	wxRadioButton* _screenCenterControl, * _worldCenterControl;
	wxChoice* _functionControl;
	wxButton* _saveControl, * _loadControl, * _centerControl;
	wxStaticText* _yMinLabel, * _yMaxLabel, * _rotationLabel;

	void AddRow(wxBoxSizer* sizer,
		const wxString& label1, wxWindow* ctrl1,
		const wxString& label2 = "", wxWindow* ctrl2 = nullptr) {
		wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
		hbox->Add(new wxStaticText(this, wxID_ANY, label1), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
		hbox->Add(ctrl1, 1, wxEXPAND | wxALL, 5);
		if (ctrl2 != nullptr) {
			hbox->Add(new wxStaticText(this, wxID_ANY, label2), 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
			hbox->Add(ctrl2, 1, wxEXPAND | wxALL, 5);
		}

		sizer->Add(hbox, 0, wxEXPAND);
	}

public:
	MainFrame() : wxFrame(NULL, wxID_ANY, "CrazyPlots") {
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
		AddRow(menuSizer, "x1", _x1Control, "y0", _y1Control);

		// Rotation
		_rotationControl = new wxScrollBar(this, wxID_ANY);
		_rotationControl->SetRange(359);

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
		wxString choices[] = { "Choice 1", "Choice 2", "Choice 3" };
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
	}

};

#endif // !MAIN_FRAME_HPP
