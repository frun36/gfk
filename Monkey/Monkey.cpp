///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Monkey.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* panelSizer;
	panelSizer = new wxBoxSizer( wxVERTICAL );

	m_canvas = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_canvas->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_canvas->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	panelSizer->Add( m_canvas, 1, wxEXPAND | wxALL, 5 );


	mainSizer->Add( panelSizer, 1, wxEXPAND, 5 );

	wxBoxSizer* menuSizer;
	menuSizer = new wxBoxSizer( wxVERTICAL );

	m_save = new wxButton( this, wxID_ANY, wxT("Save to file"), wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_save, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_onion = new wxCheckBox( this, wxID_ANY, wxT("Onion"), wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_onion, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_handControl = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	menuSizer->Add( m_handControl, 0, wxALL|wxEXPAND, 5 );

	m_handDisplay = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_handDisplay->SetValue( 50 );
	menuSizer->Add( m_handDisplay, 0, wxALL, 5 );

	m_color = new wxButton( this, wxID_ANY, wxT("Set symbol color"), wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_color, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_label = new wxTextCtrl( this, wxID_ANY, wxT("helou"), wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_label, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxString m_shapesChoices[] = { wxT("Sun"), wxT("Star"), wxT("Moon") };
	int m_shapesNChoices = sizeof( m_shapesChoices ) / sizeof( wxString );
	m_shapes = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_shapesNChoices, m_shapesChoices, 0 );
	m_shapes->SetSelection( 1 );
	menuSizer->Add( m_shapes, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	mainSizer->Add( menuSizer, 0, wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_canvas->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( MainFrame::onBgErase ), NULL, this );
	m_canvas->Connect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::repaint ), NULL, this );
	m_canvas->Connect( wxEVT_SIZE, wxSizeEventHandler( MainFrame::resize ), NULL, this );
	m_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::saveImage ), NULL, this );
	m_onion->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::toggleOnion ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_color->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::chooseColor ), NULL, this );
	m_label->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::changeLabel ), NULL, this );
	m_shapes->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::changeSymbol ), NULL, this );
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_canvas->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( MainFrame::onBgErase ), NULL, this );
	m_canvas->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MainFrame::repaint ), NULL, this );
	m_canvas->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MainFrame::resize ), NULL, this );
	m_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::saveImage ), NULL, this );
	m_onion->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MainFrame::toggleOnion ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_handControl->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( MainFrame::handleHandPositionChange ), NULL, this );
	m_color->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::chooseColor ), NULL, this );
	m_label->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::changeLabel ), NULL, this );
	m_shapes->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::changeSymbol ), NULL, this );

}
