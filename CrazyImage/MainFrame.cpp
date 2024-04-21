#include "MainFrame.hpp"


MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Main Frame", wxDefaultPosition, wxSize(1200, 800)) {
	// Create the main sizer for the frame
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create the left side of the frame for the canvas
	_canvas = new wxScrolledWindow(this, wxID_ANY);
	_canvas->SetMinSize(wxSize(400, 600)); // Adjust the size as needed
	mainSizer->Add(_canvas, 1, wxEXPAND | wxALL, 5);

	// Create the right side of the frame for the menu
	wxBoxSizer* menuSizer = new wxBoxSizer(wxVERTICAL);

	// Add buttons to the menu
	_buttonDefault = new wxButton(this, wxID_ANY, "Default");
	menuSizer->Add(_buttonDefault, 0, wxEXPAND | wxALL, 5);

	wxGridSizer* gridSizer = new wxGridSizer(4, 2, 5, 5);
	_buttonGrayscale = new wxButton(this, wxID_ANY, "Grayscale");
	_buttonBlur = new wxButton(this, wxID_ANY, "Blur");
	_buttonMirror = new wxButton(this, wxID_ANY, "Mirror");
	_buttonReplace = new wxButton(this, wxID_ANY, "Replace");
	_buttonRescale = new wxButton(this, wxID_ANY, "Rescale");
	_buttonRotate = new wxButton(this, wxID_ANY, "Rotate");
	_buttonRotateHue = new wxButton(this, wxID_ANY, "Rotate Hue");
	_buttonMask = new wxButton(this, wxID_ANY, "Mask");
	_buttonPrewitt = new wxButton(this, wxID_ANY, "Prewitt");
	_buttonThresh = new wxButton(this, wxID_ANY, "Thresh");

	gridSizer->Add(_buttonGrayscale, 0, wxEXPAND | wxALL, 5);
	gridSizer->Add(_buttonBlur, 0, wxEXPAND | wxALL, 5);
	gridSizer->Add(_buttonMirror, 0, wxEXPAND | wxALL, 5);
	gridSizer->Add(_buttonReplace, 0, wxEXPAND | wxALL, 5);
	gridSizer->Add(_buttonRescale, 0, wxEXPAND | wxALL, 5);
	gridSizer->Add(_buttonRotate, 0, wxEXPAND | wxALL, 5);
	gridSizer->Add(_buttonRotateHue, 0, wxEXPAND | wxALL, 5);
	gridSizer->Add(_buttonMask, 0, wxEXPAND | wxALL, 5);
	menuSizer->Add(gridSizer, 0, wxEXPAND | wxALL, 5);

	// Add sliders to the menu with labels above them
	wxStaticText* labelBrightness = new wxStaticText(this, wxID_ANY, "Brightness");
	_sliderBrightness = new wxSlider(this, wxID_ANY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	menuSizer->Add(labelBrightness, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
	menuSizer->Add(_sliderBrightness, 0, wxEXPAND | wxALL, 5);

	wxStaticText* labelContrast = new wxStaticText(this, wxID_ANY, "Contrast");
	_sliderContrast = new wxSlider(this, wxID_ANY, 0, -100, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	menuSizer->Add(labelContrast, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
	menuSizer->Add(_sliderContrast, 0, wxEXPAND | wxALL, 5);

	// Add the remaining buttons to the menu
	menuSizer->Add(_buttonPrewitt, 0, wxEXPAND | wxALL, 5);
	menuSizer->Add(_buttonThresh, 0, wxEXPAND | wxALL, 5);

	// Add the menuSizer to the mainSizer
	mainSizer->Add(menuSizer, 0, wxEXPAND | wxALL, 5);

	// Set the main sizer for the frame
	SetSizer(mainSizer);
}
