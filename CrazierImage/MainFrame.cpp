#include "MainFrame.hpp"

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Main Frame", wxDefaultPosition, wxDefaultSize) {
	// Create the main sizer for the frame
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create the menu sizer
	wxBoxSizer* menuSizer = new wxBoxSizer(wxVERTICAL);

	// Add controls to the menu
	_bLoad = new wxButton(this, wxID_ANY, "Load image");
	_bCensor = new wxButton(this, wxID_ANY, "Censor");
	_bErode = new wxButton(this, wxID_ANY, "Erode");
	_cbAnimate = new wxCheckBox(this, wxID_ANY, "Animate");
	_teExif = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_NO_VSCROLL);

	menuSizer->Add(_bLoad, 0, wxEXPAND | wxALL, 5);
	menuSizer->Add(_bCensor, 0, wxEXPAND | wxALL, 5);
	menuSizer->Add(_bErode, 0, wxEXPAND | wxALL, 5);
	menuSizer->Add(_cbAnimate, 0, wxEXPAND | wxALL, 5);
	menuSizer->Add(_teExif, 1, wxEXPAND | wxALL, 5);


	mainSizer->Add(menuSizer, 0, wxEXPAND | wxALL, 5);
	SetSizer(mainSizer);

	// Create the canvas
	_canvas = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(960, 540), wxTAB_TRAVERSAL);
	_canvas->SetBackgroundColour(wxColor(0, 0, 0));
	mainSizer->Add(_canvas, 1, wxEXPAND | wxALL, 5);
	Fit();

	// Events
	_canvas->Bind(wxEVT_UPDATE_UI, [this](wxUpdateUIEvent&) { /*_repaint();*/  });
}

void MainFrame::_repaint() {
	
}