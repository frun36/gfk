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

	void _addSliderWithLabelAndValue(
		wxBoxSizer* sizer,
		const wxString& label,
		wxSlider** slider,
		int minValue,
		int maxValue,
		int startValue,
        std::string startLabel,
		std::function<double(wxScrollEvent&)> scrollHandler
	);

	void _uploadImage();

    void _displayConfig() {
        _rotX->SetValue(static_cast<int>(_config.getRotX()));
        _rotY->SetValue(static_cast<int>(_config.getRotY()));
        _rotZ->SetValue(static_cast<int>(_config.getRotZ()));

        _transX->SetValue(static_cast<int>(_config.getTransX() * 100));
        _transY->SetValue(static_cast<int>(_config.getTransY() * 100));
        _transZ->SetValue(static_cast<int>(_config.getTransZ() * 100));

        _scaleX->SetValue(static_cast<int>(_config.getScaleX() * 100));
        _scaleY->SetValue(static_cast<int>(_config.getScaleY() * 100));
        _scaleZ->SetValue(static_cast<int>(_config.getScaleZ() * 100));
    }

    void _updateConfig() {
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


public:
	MainFrame();
};

