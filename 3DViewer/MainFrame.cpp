#include "MainFrame.hpp"

#include <functional>
#include <format>

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "3DViewer") {
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

	// Create a vertical sizer for sliders
	wxBoxSizer* menuSizer = new wxBoxSizer(wxVERTICAL);

	_load = new wxButton(this, wxID_ANY, "Load model");
	menuSizer->Add(_load, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	// Add sliders with labels and value labels
	addSliderWithLabelAndValue(menuSizer, "X Translation", &_transX, -200, 200, 0, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	addSliderWithLabelAndValue(menuSizer, "Y Translation", &_transY, -200, 200, 0, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	addSliderWithLabelAndValue(menuSizer, "Z Translation", &_transZ, -200, 200, 0, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });

	addSliderWithLabelAndValue(menuSizer, "X Rotation", &_rotX, 0, 360, 0, [](wxScrollEvent& e) { return e.GetInt(); });
	addSliderWithLabelAndValue(menuSizer, "Y Rotation", &_rotY, 0, 360, 0, [](wxScrollEvent& e) { return e.GetInt(); });
	addSliderWithLabelAndValue(menuSizer, "Z Rotation", &_rotZ, 0, 360, 0, [](wxScrollEvent& e) { return e.GetInt(); });

	addSliderWithLabelAndValue(menuSizer, "X Scale", &_scaleX, 1, 200, 100, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	addSliderWithLabelAndValue(menuSizer, "Y Scale", &_scaleY, 1, 200, 100, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	addSliderWithLabelAndValue(menuSizer, "Z Scale", &_scaleZ, 1, 200, 100, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });

	_reset = new wxButton(this, wxID_ANY, "Reset transform");
	menuSizer->Add(_reset, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	mainSizer->Add(menuSizer, 0, wxEXPAND, 5);

	this->SetSizer(mainSizer);
	this->Layout();
	this->Centre(wxBOTH);
}

void MainFrame::addSliderWithLabelAndValue(wxBoxSizer* sizer, const wxString& label, wxSlider** slider, int minValue, int maxValue, int startValue, std::function<double(wxScrollEvent&)> scrollHandler) {
	wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* labelText = new wxStaticText(this, wxID_ANY, label + ": ");
	rowSizer->Add(labelText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	*slider = new wxSlider(this, wxID_ANY, startValue, minValue, maxValue, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	rowSizer->Add(*slider, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxStaticText* valueText = new wxStaticText(this, wxID_ANY, wxString::Format("%d", startValue));
	valueText->SetMinSize(wxSize(64, -1));
	rowSizer->Add(valueText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	(*slider)->Bind(wxEVT_SCROLL_TOP, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_BOTTOM, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_LINEUP, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_LINEDOWN, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_PAGEUP, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_PAGEDOWN, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_THUMBTRACK, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_THUMBRELEASE, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});

	(*slider)->Bind(wxEVT_SCROLL_CHANGED, [this, scrollHandler, valueText](wxScrollEvent& e) {
		valueText->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		});


	sizer->Add(rowSizer, 0, wxEXPAND | wxALL, 5);
}

