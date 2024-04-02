///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
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
	
	m_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	panelSizer->Add( m_panel, 1, wxEXPAND | wxALL, 5 );
	
	
	mainSizer->Add( panelSizer, 1, wxEXPAND, 5 );
	
	wxBoxSizer* menuSizer;
	menuSizer = new wxBoxSizer( wxVERTICAL );
	
	m_save = new wxButton( this, wxID_ANY, wxT("Save to file"), wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_save, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_banana = new wxCheckBox( this, wxID_ANY, wxT("Banana"), wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_banana, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_handControl = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	menuSizer->Add( m_handControl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_handDisplay = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_handDisplay->SetValue( 0 ); 
	menuSizer->Add( m_handDisplay, 0, wxALL, 5 );
	
	m_color = new wxButton( this, wxID_ANY, wxT("MyButton"), wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_color, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_label = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	menuSizer->Add( m_label, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxArrayString m_shapesChoices;
	m_shapes = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_shapesChoices, 0 );
	m_shapes->SetSelection( 0 );
	menuSizer->Add( m_shapes, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	mainSizer->Add( menuSizer, 0, wxEXPAND, 5 );
	
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}
