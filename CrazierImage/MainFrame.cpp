#include "MainFrame.hpp"
#include <vector>

//#include "CImg.h"
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

}

void MainFrame::_repaint() {
	if (!_imgMod.IsOk()) return;

	wxClientDC dc(_canvas);
	_imgMod.Rescale(_canvas->GetSize().x, _canvas->GetSize().y);
	wxBitmap bmp(_imgMod);
	dc.DrawBitmap(bmp, 0, 0);
}

void MainFrame::_loadImage() {
	wxFileDialog loadFileDialog(this, "Choose a file", "", "", "Image Files (*.jpg)|*.jpg");
	if (loadFileDialog.ShowModal() == wxID_CANCEL) return;

	wxString path = loadFileDialog.GetPath();

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