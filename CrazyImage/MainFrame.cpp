#include "MainFrame.hpp"

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "Main Frame", wxDefaultPosition, wxSize(1200, 800)) {
	// Create the main sizer for the frame
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create the left side of the frame for the canvas
	_canvas = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	_canvas->SetScrollRate(5, 5);
	_canvas->SetScrollbars(25, 25, 52, 40);
	_canvas->SetBackgroundColour(wxColor(0, 0, 0));
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
	_buttonExtra = new wxButton(this, wxID_ANY, "Extra");

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
	menuSizer->Add(_buttonExtra, 0, wxEXPAND | wxALL, 5);


	mainSizer->Add(menuSizer, 0, wxEXPAND | wxALL, 5);
	SetSizer(mainSizer);

	// Events
	_canvas->Bind(wxEVT_UPDATE_UI, [this](wxUpdateUIEvent&) { _repaint();  });

	_buttonDefault->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Copy();
		_canvas->Refresh();
		_sliderBrightness->SetValue(0);
		_sliderContrast->SetValue(0);
		});

	_buttonGrayscale->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.ConvertToGreyscale();
		_canvas->Refresh();
		});

	_buttonBlur->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Blur(5);
		_canvas->Refresh();
		});

	_buttonMirror->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Mirror();
		_canvas->Refresh();
		});

	_buttonReplace->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Copy();
		imgMod.Replace(254, 0, 0, 0, 0, 255);
		_canvas->Refresh();
		});

	_buttonRescale->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Copy().Rescale(320, 240);
		_canvas->Refresh();
		});

	_buttonRotate->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Rotate(M_PI / 6, wxPoint(imgOrg.GetWidth() * 0.5, imgOrg.GetHeight() * 0.5));
		_canvas->Refresh();
		});

	_buttonRotateHue->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Copy();
		imgMod.RotateHue(0.5);
		_canvas->Refresh();
		});

	_buttonMask->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Copy();
		imgMod.SetMaskFromImage(imgMask, 0, 0, 0);
		_canvas->Refresh();
		});

	auto brightness = [this](wxScrollEvent& event) {
		imgMod = _brightness(imgOrg, event.GetPosition());
		_canvas->Refresh();
		};

	_sliderBrightness->Bind(wxEVT_SCROLL_TOP, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_BOTTOM, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_LINEUP, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_LINEDOWN, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_PAGEUP, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_PAGEDOWN, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_THUMBTRACK, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_THUMBRELEASE, brightness);
	_sliderBrightness->Bind(wxEVT_SCROLL_CHANGED, brightness);


	auto contrast = [this](wxScrollEvent& event) {
		imgMod = _contrast(imgOrg, event.GetPosition());
		_canvas->Refresh();
		};

	_sliderContrast->Bind(wxEVT_SCROLL_TOP, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_BOTTOM, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_LINEUP, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_LINEDOWN, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_PAGEUP, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_PAGEDOWN, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_THUMBTRACK, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_THUMBRELEASE, contrast);
	_sliderContrast->Bind(wxEVT_SCROLL_CHANGED, contrast);


	_buttonPrewitt->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = _prewitt(imgOrg);
		_canvas->Refresh();
		});

	_buttonThresh->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = _thresh(imgOrg, 128);
		_canvas->Refresh();
		});

	_buttonExtra->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		imgMod = imgOrg.Copy();
		unsigned char* data = imgMod.GetData();
		float r, g, b, new_r, new_g, new_b;
		for (size_t i = 0; i < imgMod.GetWidth() * imgMod.GetHeight(); i++) {
			r = data[3 * i] / 255.f;
			g = data[3 * i + 1] / 255.f;
			b = data[3 * i + 2] / 255.f;

			new_r = 0.5 * sin(2 * M_PI * r) + 0.5;
			new_g = 0.25 * (sin(2 * M_PI * g) + cos(2 * M_PI * r) + 2);
			new_b = 0.5 * cos(2 * M_PI * b) + 0.5;

			data[3 * i] = static_cast<unsigned char>(255 * new_r);
			data[3 * i + 1] = static_cast<unsigned char>(255 * new_g);
			data[3 * i + 2] = static_cast<unsigned char>(255 * new_b);
		}
		});
}

void MainFrame::_repaint() {
	wxBitmap bitmap(imgMod);
	wxClientDC dc(_canvas);
	_canvas->DoPrepareDC(dc);
	dc.DrawBitmap(bitmap, 0, 0, true);
}

wxImage MainFrame::_brightness(wxImage& img, int brightness) {
	wxImage newImg = img.Copy();

	unsigned char* data = newImg.GetData();

	for (size_t i = 0; i < 3 * static_cast<size_t>(newImg.GetWidth()) * newImg.GetHeight(); i++) {
		if (255 - data[i] < brightness) data[i] = 255;
		else if (data[i] < -brightness) data[i] = 0;
		else data[i] = data[i] + brightness;
	}

	return newImg;
}

wxImage MainFrame::_contrast(wxImage& img, int contrast) {
	float c = (100.0 + static_cast<float>(contrast)) / (101.0 - static_cast<float>(contrast));
	float val;

	wxImage newImg = img.Copy();
	unsigned char* data = newImg.GetData();

	for (size_t i = 0; i < 3 * static_cast<size_t>(newImg.GetWidth()) * newImg.GetHeight(); i++) {
		val = (data[i] - 127) * c + 127;

		if (val > 255) data[i] = 255;
		else if (val < 0) data[i] = 0;
		else data[i] = static_cast<unsigned char>(val);
	}

	return newImg;
}

wxImage MainFrame::_prewitt(wxImage& img) {
	wxImage newImg = img.Copy();

	unsigned char* originalData = img.GetData();
	unsigned char* data = newImg.GetData();

	size_t x = img.GetWidth();
	size_t y = img.GetHeight();

	int tmp = 0;

	for (size_t i = 1; i < y - 1; i++) {
		for (size_t j = 1; j < x - 1; j++) {
			for (size_t k = 0; k < 3; k++) {
				tmp = 0;

				tmp -= originalData[3 * ((i - 1) * x + j - 1) + k];
				tmp += originalData[3 * ((i - 1) * x + j + 1) + k];
				tmp -= originalData[3 * (i * x + j - 1) + k];
				tmp += originalData[3 * (i * x + j + 1) + k];
				tmp -= originalData[3 * ((i + 1) * x + j - 1) + k];
				tmp += originalData[3 * ((i + 1) * x + j + 1) + k];

				data[3 * (i * x + j) + k] = abs(tmp) / 3.0;
			}
		}
	}

	return newImg;
}

wxImage MainFrame::_thresh(wxImage& img, unsigned char thresh) {
	wxImage newImg = img.Copy();
	unsigned char* data = newImg.GetData();

	for (size_t i = 0; i < static_cast<size_t>(3) * newImg.GetWidth() * newImg.GetHeight(); i++)
		data[i] = data[i] > thresh ? 255 : 0;

	return newImg;
}
