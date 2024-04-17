#include "MainFrame.hpp"

#include <functional>
#include <format>
#include <fstream>
#include <iostream>

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "3DViewer"), _config(), _model(_config) {
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
	_addSliderWithLabelAndValue(menuSizer, "X Translation", &_transX, &_transXLabel, -200, 200, 0, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	_addSliderWithLabelAndValue(menuSizer, "Y Translation", &_transY, &_transYLabel, -200, 200, 0, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	_addSliderWithLabelAndValue(menuSizer, "Z Translation", &_transZ, &_transZLabel, -200, 200, 0, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });

	_addSliderWithLabelAndValue(menuSizer, "X Rotation", &_rotX, &_rotXLabel, 0, 360, 0, [](wxScrollEvent& e) { return e.GetInt(); });
	_addSliderWithLabelAndValue(menuSizer, "Y Rotation", &_rotY, &_rotYLabel, 0, 360, 0, [](wxScrollEvent& e) { return e.GetInt(); });
	_addSliderWithLabelAndValue(menuSizer, "Z Rotation", &_rotZ, &_rotZLabel, 0, 360, 0, [](wxScrollEvent& e) { return e.GetInt(); });

	_addSliderWithLabelAndValue(menuSizer, "X Scale", &_scaleX, &_scaleXLabel, 1, 200, 100, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	_addSliderWithLabelAndValue(menuSizer, "Y Scale", &_scaleY, &_scaleYLabel, 1, 200, 100, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });
	_addSliderWithLabelAndValue(menuSizer, "Z Scale", &_scaleZ, &_scaleZLabel, 1, 200, 100, [](wxScrollEvent& e) { return e.GetInt() * 0.01; });

	_reset = new wxButton(this, wxID_ANY, "Reset transform");
	menuSizer->Add(_reset, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	mainSizer->Add(menuSizer, 0, wxEXPAND, 5);

	_load->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		_uploadImage();
		});

	_reset->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		_config.reset();
		_displayConfig();
		_canvas->Refresh();
		});

	this->SetSizer(mainSizer);
	this->Layout();
	this->Centre(wxBOTH);

	_canvas->SetBackgroundStyle(wxBG_STYLE_PAINT);

	_canvas->Bind(wxEVT_UPDATE_UI, [this](wxUpdateUIEvent&) {
		wxClientDC dc1(_canvas);
		wxBufferedDC dc(&dc1);

		dc.SetBrush(*wxWHITE_BRUSH);
		dc.Clear();

		int w, h;
		_canvas->GetSize(&w, &h);

		_model.draw(dc, w, h);
		});

	_displayConfig();
}

void MainFrame::_addSliderWithLabelAndValue(wxBoxSizer* sizer, const wxString& label, wxSlider** slider, wxStaticText** valueText, int minValue, int maxValue, int startValue, std::function<double(wxScrollEvent&)> scrollHandler) {
	wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* labelText = new wxStaticText(this, wxID_ANY, label + ": ");
	rowSizer->Add(labelText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	*slider = new wxSlider(this, wxID_ANY, startValue, minValue, maxValue, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	rowSizer->Add(*slider, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	*valueText = new wxStaticText(this, wxID_ANY, "-");
	(*valueText)->SetMinSize(wxSize(64, -1));
	rowSizer->Add(*valueText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	auto eventHandler = [this, scrollHandler, valueText](wxScrollEvent& e) {
		(*valueText)->SetLabelText(wxString::Format("%.2f", scrollHandler(e)));
		_updateConfig();
		_canvas->Refresh(); 
		};

	(*slider)->Bind(wxEVT_SCROLL_TOP, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_BOTTOM, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_LINEUP, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_LINEDOWN, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_PAGEUP, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_PAGEDOWN, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_THUMBTRACK, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_THUMBRELEASE, eventHandler);
	(*slider)->Bind(wxEVT_SCROLL_CHANGED, eventHandler);

	sizer->Add(rowSizer, 0, wxEXPAND | wxALL, 5);
}

void MainFrame::_uploadImage() {
	wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (WxOpenFileDialog.ShowModal() == wxID_OK)
	{
		double x1, y1, z1, x2, y2, z2;
		unsigned r, g, b;

		Mesh mesh;

		std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
		if (in.is_open()) {
			while (!in.eof()) {
				in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
				mesh.addSegment(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
			}
			in.close();

			_model.setMesh(std::move(mesh));
		}
	}

	_canvas->Refresh();
}

void MainFrame::_displayConfig() {
	_rotX->SetValue(static_cast<int>(_config.getRotX()));
	_rotY->SetValue(static_cast<int>(_config.getRotY()));
	_rotZ->SetValue(static_cast<int>(_config.getRotZ()));

	_transX->SetValue(static_cast<int>(_config.getTransX() * 100));
	_transY->SetValue(static_cast<int>(_config.getTransY() * 100));
	_transZ->SetValue(static_cast<int>(_config.getTransZ() * 100));

	_scaleX->SetValue(static_cast<int>(_config.getScaleX() * 100));
	_scaleY->SetValue(static_cast<int>(_config.getScaleY() * 100));
	_scaleZ->SetValue(static_cast<int>(_config.getScaleZ() * 100));

	_rotXLabel->SetLabelText(wxString::Format("%.2f", _config.getRotX()));
	_rotYLabel->SetLabelText(wxString::Format("%.2f", _config.getRotY()));
	_rotZLabel->SetLabelText(wxString::Format("%.2f", _config.getRotZ()));

	_transXLabel->SetLabelText(wxString::Format("%.2f", _config.getTransX()));
	_transYLabel->SetLabelText(wxString::Format("%.2f", _config.getTransY()));
	_transZLabel->SetLabelText(wxString::Format("%.2f", _config.getTransZ()));

	_scaleXLabel->SetLabelText(wxString::Format("%.2f", _config.getScaleX()));
	_scaleYLabel->SetLabelText(wxString::Format("%.2f", _config.getScaleY()));
	_scaleZLabel->SetLabelText(wxString::Format("%.2f", _config.getScaleZ()));
}

void MainFrame::_updateConfig() {
	_config.setRotX(_rotX->GetValue());
	_config.setRotY(_rotY->GetValue());
	_config.setRotZ(_rotZ->GetValue());

	_config.setTransX(_transX->GetValue() * 0.01);
	_config.setTransY(_transY->GetValue() * 0.01);
	_config.setTransZ(_transZ->GetValue() * 0.01);

	_config.setScaleX(_scaleX->GetValue() * 0.01);
	_config.setScaleY(_scaleY->GetValue() * 0.01);
	_config.setScaleZ(_scaleZ->GetValue() * 0.01);
}
