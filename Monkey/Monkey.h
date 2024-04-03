///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.1.0-0-g733bf3d)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:

	protected:
		wxPanel* m_canvas;
		wxButton* m_save;
		wxCheckBox* m_onion;
		wxScrollBar* m_handControl;
		wxGauge* m_handDisplay;
		wxButton* m_color;
		wxTextCtrl* m_label;
		wxChoice* m_shapes;

		// Virtual event handlers, override them in your derived class
		virtual void onBgErase( wxEraseEvent& event ) { event.Skip(); }
		virtual void repaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void resize( wxSizeEvent& event ) { event.Skip(); }
		virtual void saveImage( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleOnion( wxCommandEvent& event ) { event.Skip(); }
		virtual void handleHandPositionChange( wxScrollEvent& event ) { event.Skip(); }
		virtual void chooseColor( wxCommandEvent& event ) { event.Skip(); }
		virtual void changeLabel( wxCommandEvent& event ) { event.Skip(); }
		virtual void changeSymbol( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,1000 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrame();

};

