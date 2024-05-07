#include "MainFrame.hpp"
#include "Linalg.hpp"
#include "Plot.hpp"
#include <wx/dcbuffer.h>

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Voxel", wxDefaultPosition, wxSize(530, 750)), _config() {
	/*this->SetSizeHints(wxDefaultSize, wxSize(530, 650));*/

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	_canvas = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500), wxTAB_TRAVERSAL);
	_canvas->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNHIGHLIGHT));
	_canvas->SetMinSize(wxSize(500, 500));
	_canvas->SetMaxSize(wxSize(500, 500));

	bSizer1->Add(_canvas, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Choose function:")), wxHORIZONTAL);

	_button1 = new wxButton(sbSizer1->GetStaticBox(), wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0);
	_button1->SetMinSize(wxSize(40, 40));
	_button1->SetMaxSize(wxSize(40, 40));

	sbSizer1->Add(_button1, 0, wxALL, 5);

	_button2 = new wxButton(sbSizer1->GetStaticBox(), wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0);
	_button2->SetMinSize(wxSize(40, 40));
	_button2->SetMaxSize(wxSize(40, 40));

	sbSizer1->Add(_button2, 0, wxALL, 5);

	_button3 = new wxButton(sbSizer1->GetStaticBox(), wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, 0);
	_button3->SetMinSize(wxSize(40, 40));

	sbSizer1->Add(_button3, 0, wxALL, 5);

	_button4 = new wxButton(sbSizer1->GetStaticBox(), wxID_ANY, wxT("4"), wxDefaultPosition, wxDefaultSize, 0);
	_button4->SetMinSize(wxSize(40, 40));
	_button4->SetMaxSize(wxSize(40, 40));

	sbSizer1->Add(_button4, 0, wxALL, 5);
	bSizer2->Add(sbSizer1, 0, 0, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);


	bSizer5->Add(10, 0, 0, 0, 5);
	_stRotation = new wxStaticText(this, wxID_ANY, wxT("Rotation: 133 deg"), wxDefaultPosition, wxDefaultSize, 0);
	_stRotation->Wrap(-1);
	bSizer5->Add(_stRotation, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT, 5);


	bSizer5->Add(0, 0, 1, wxEXPAND, 5);
	_cbColor = new wxCheckBox(this, wxID_ANY, wxT("Color"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer5->Add(_cbColor, 1, wxALIGN_CENTER_VERTICAL, 5);


	bSizer4->Add(bSizer5, 1, wxEXPAND, 5);

	_sRotation = new wxSlider(this, wxID_ANY, 133, 0, 360, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	bSizer4->Add(_sRotation, 1, wxALL | wxEXPAND, 5);

	bSizer2->Add(bSizer4, 1, wxEXPAND, 5);
	bSizer1->Add(bSizer2, 0, wxEXPAND, 5);

	_sTilt = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	bSizer1->Add(_sTilt, 0, wxALL | wxEXPAND, 5);

	_canvas->Bind(wxEVT_UPDATE_UI, [this](wxUpdateUIEvent&) { _repaint(); });
	_canvas->SetBackgroundStyle(wxBG_STYLE_PAINT);

	_button1->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		_config.setFunction([](double x, double y) { return x + y; });
		_canvas->Refresh();
		});

	_button2->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		_config.setFunction([](double x, double y) { return x + y; });
		_canvas->Refresh();
		});

	_button3->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		_config.setFunction([](double x, double y) { return x + y; });
		_canvas->Refresh();
		});

	_button4->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		_config.setFunction([](double x, double y) { return x + y; });
		_canvas->Refresh();
		});

	auto updateRotation = [this](wxScrollEvent& event) {
		_config.setRotation(event.GetPosition());
		_stRotation->SetLabelText(wxString::Format("Rotation: %d deg", _config.getRotation()));
		_canvas->Refresh();
		};

	auto updateTilt = [this](wxScrollEvent& event) {
		_config.setTilt(event.GetPosition());
		_canvas->Refresh();
		};

	_sRotation->Bind(wxEVT_SCROLL_TOP, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_BOTTOM, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_LINEUP, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_LINEDOWN, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_PAGEUP, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_PAGEDOWN, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_THUMBTRACK, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_THUMBRELEASE, updateRotation);
	_sRotation->Bind(wxEVT_SCROLL_CHANGED, updateRotation);

	_sTilt->Bind(wxEVT_SCROLL_TOP, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_BOTTOM, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_LINEUP, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_LINEDOWN, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_PAGEUP, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_PAGEDOWN, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_THUMBTRACK, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_THUMBRELEASE, updateTilt);
	_sTilt->Bind(wxEVT_SCROLL_CHANGED, updateTilt);

	_cbColor->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& event) {
		_config.setColor(event.IsChecked());
		_canvas->Refresh();
		});

	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);
}

void MainFrame::_repaint() {
	wxClientDC dc1(_canvas);
	wxBufferedDC dc(&dc1);

	Plot plt(_config, 5);
	plt.draw(dc);
}