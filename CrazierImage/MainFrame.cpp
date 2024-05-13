#include "MainFrame.hpp"
#include <vector>

#include "FreeImagePlus.h"

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, "CrazierImage", wxDefaultPosition, wxDefaultSize) {
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
	_canvas = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 533), wxTAB_TRAVERSAL);
	_canvas->SetBackgroundColour(wxColor(0, 0, 0));
	mainSizer->Add(_canvas, 1, wxEXPAND | wxALL, 5);
	Fit();

	// Events
	_canvas->Bind(wxEVT_UPDATE_UI, [this](wxUpdateUIEvent&) { _repaint();  });

	_bLoad->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) { _loadImage(); });
	
	_bCensor->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {
		auto cImg = wxImageAsCImg(_imgOrg);

		int x0 = 460;
		int y0 = 10;
		int dx = 120;
		int dy = 100;
		auto cropped = cImg.get_crop(x0, y0, x0 + dx, y0 + dy);
		cropped.blur(8);
		cImg.draw_image(x0, y0, cropped);

		_imgMod = cImgAsWxImage(cImg);
		_canvas->Refresh();
		});
}

void MainFrame::_repaint() {
	if (!_imgMod.IsOk()) return;

	wxClientDC dc(_canvas);
	_imgMod.Rescale(_canvas->GetSize().x, _canvas->GetSize().y);
	wxBitmap bmp(_imgMod);
	dc.DrawBitmap(bmp, 0, 0);
}

void MainFrame::_loadImage() {
	//wxFileDialog loadFileDialog(this, "Choose a file", "", "", "Image Files (*.jpg)|*.jpg");
	//if (loadFileDialog.ShowModal() == wxID_CANCEL) return;

	//wxString path = loadFileDialog.GetPath();

	wxString path = "test.jpg";

	_handleExif(path);

	if (!_imgOrg.LoadFile(path)) {
		wxMessageBox("Couldn't open image");
		return;
	}

	_imgMod = _imgOrg.Copy();

	Refresh();
}

void MainFrame::_handleExif(const wxString& name) {
	fipImage img;
	img.load(name);

	unsigned width = img.getWidth();
	unsigned height = img.getHeight();

	if (!img.isValid())
		wxMessageBox("Couldn't load image");

	fipTag tag;
	fipMetadataFind finder;

	wxString info = "";

	if (finder.findFirstMetadata(FIMD_EXIF_MAIN, img, tag)) do {
		info += wxString::Format("%s: %s\r\n", tag.getKey(), tag.toString(FIMD_EXIF_MAIN));
	} while (finder.findNextMetadata(tag));

	_teExif->SetLabelText(info);
}

cimg_library::CImg<unsigned char> MainFrame::wxImageAsCImg(const wxImage& img) {
	cimg_library::CImg<unsigned char> newImg(img.GetWidth(), img.GetHeight(), 1, 3);

	/*size_t size = img.GetWidth() * img.GetHeight() * 3;

	unsigned char* data = (unsigned char*)malloc(size);
	memcpy(data, img.GetData(), size);

	newImg.assign(data, img.GetWidth(), img.GetHeight(), 1, 3);*/

	for (size_t y = 0; y < img.GetHeight(); y++)	{
		for (size_t x = 0; x < img.GetWidth(); x++) {
			newImg(x, y, 0, 0) = img.GetRed(x, y);
			newImg(x, y, 0, 1) = img.GetGreen(x, y);
			newImg(x, y, 0, 2) = img.GetBlue(x, y);
		}
	}

	return newImg;
}

wxImage MainFrame::cImgAsWxImage(const cimg_library::CImg<unsigned char>& img) {
	wxImage newImg(img.width(), img.height());

	/*size_t size = newImg.GetWidth() * newImg.GetHeight() * 3;

	unsigned char* data = (unsigned char*)malloc(size);

	memcpy(data, img.data(), size);

	newImg.SetData(data);*/

	for (size_t y = 0; y < img.height(); y++) {
		for (size_t x = 0; x < img.width(); x++) {
			newImg.SetRGB(x, y, img(x, y, 0, 0), img(x, y, 0, 1), img(x, y, 0, 2));
		}
	}

	return newImg;
}



