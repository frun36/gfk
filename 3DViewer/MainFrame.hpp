#pragma once

#include <wx/wx.h>

class MainFrame : public wxFrame {
private:
	wxPanel* _canvas;

	wxButton* _load, * _reset;

	wxSlider* _rotX, * _rotY, * _rotZ;
	wxSlider* _transX, * _transY, * _transZ;
	wxSlider* _scaleX, * _scaleY, * _scaleZ;

	void addSliderWithLabelAndValue(wxBoxSizer* sizer, const wxString& label, wxSlider** slider, int minValue, int maxValue, int startValue, std::function<double(wxScrollEvent&)> scrollHandler);
public:
	MainFrame();
};

