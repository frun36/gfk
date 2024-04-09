#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <memory>

#include "Config.hpp"
#include "Plot.hpp"

#include <format>

class MainFrame : public wxFrame {
private:
	std::shared_ptr<Config> _config;
	wxPanel* _canvas;
	wxTextCtrl* _x0Control, * _y0Control, * _x1Control, * _y1Control, * _xTransControl, * _yTransControl, * _xStartControl, * _xEndControl;
	wxScrollBar* _rotationControl;
	wxRadioButton* _screenCenterControl, * _worldCenterControl;
	wxChoice* _functionControl;
	wxButton* _saveControl, * _loadControl, * _centerControl;
	wxStaticText* _yMinLabel, * _yMaxLabel, * _rotationLabel;

	void AddRow(wxBoxSizer* sizer,
		const wxString& label1, wxWindow* ctrl1,
		const wxString& label2 = "", wxWindow* ctrl2 = nullptr);

	void repaint();

	void repaintEventHandler(wxUpdateUIEvent& event) { repaint(); }

	void displayConfig() {
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

public:
	MainFrame(std::shared_ptr<Config> config);

	~MainFrame();
};

#endif // !MAIN_FRAME_HPP
