#pragma once

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <memory>

#include "Config.hpp"
#include "Model.hpp"

class MainFrame : public wxFrame {
private:
	Config _config;
	Model _model;

	wxPanel* _canvas;

	wxButton* _load, * _reset;

	wxSlider* _rotX, * _rotY, * _rotZ;
	wxSlider* _transX, * _transY, * _transZ;
	wxSlider* _scaleX, * _scaleY, * _scaleZ;

    wxStaticText* _rotXLabel, * _rotYLabel, * _rotZLabel;
    wxStaticText* _transXLabel, * _transYLabel, * _transZLabel;
    wxStaticText* _scaleXLabel, * _scaleYLabel, * _scaleZLabel;

	void _addSliderWithLabelAndValue(
		wxBoxSizer* sizer,
		const wxString& label,
		wxSlider** slider,
        wxStaticText** valueText,
		int minValue,
		int maxValue,
		int startValue,
		std::function<double(wxScrollEvent&)> scrollHandler
	);

	void _uploadImage();

    void _displayConfig();

    void _updateConfig();


public:
	MainFrame();
};

