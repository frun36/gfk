#ifndef __MonkeyMainFrame__
#define __MonkeyMainFrame__

/**
@file
Subclass of MainFrame, which is generated by wxFormBuilder.
*/

#include "Monkey.h"

//// end generated include
#include <wx/wx.h>
#include <wx/colordlg.h>

/** Implementing MainFrame */
class MonkeyMainFrame : public MainFrame
{
	protected:
		// Handlers for MainFrame events.
		void onBgErase( wxEraseEvent& event );
		void repaint( wxPaintEvent& event );
		void resize( wxSizeEvent& event );
		void saveImage( wxCommandEvent& event );
		void toggleOnion( wxCommandEvent& event );
		void handleHandPositionChange( wxScrollEvent& event );
		void chooseColor( wxCommandEvent& event );
		void changeLabel( wxCommandEvent& event );
		void changeSymbol( wxCommandEvent& event );
	public:
		/** Constructor */
		MonkeyMainFrame( wxWindow* parent );
	//// end generated class members

	private:
		wxImage m_onionImg;
		wxBitmap m_onionBitmap;


		bool m_hasOnion;

		wxPoint m_onionPosition;

		void setOnionPosition(double frac) {
			m_onionPosition = wxPoint(200, 150 - frac * 100);
		}

		enum Symbol { SUN, STAR, MOON } m_symbol;

		wxPoint m_starVertices[6];

		wxBrush m_starBrush;




};

#endif // __MonkeyMainFrame__
