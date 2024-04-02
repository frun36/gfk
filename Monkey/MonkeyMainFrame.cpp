#include "MonkeyMainFrame.h"

MonkeyMainFrame::MonkeyMainFrame(wxWindow* parent)
	:
	MainFrame(parent)
{
	m_img.AddHandler(new wxPNGHandler);
	m_img.LoadFile("onion.png", wxBITMAP_TYPE_PNG);
	m_onion = wxBitmap(m_img);
}

void MonkeyMainFrame::repaint(wxPaintEvent& event)
{
	wxClientDC dc(m_canvas);
	dc.SetDeviceOrigin(100, 100);
	dc.SetPen(*wxTRANSPARENT_PEN);

	// Head
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawRectangle(0, 0, 100, 120);
	dc.DrawRectangle(15, -40, 10, 40);
	dc.DrawRectangle(75, -40, 10, 40);

	// Mouth
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawCircle(wxPoint(50, 70), 30);
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawCircle(wxPoint(50, 50), 40);

	// Eyes
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawCircle(wxPoint(30, 30), 10);
	dc.DrawCircle(wxPoint(70, 30), 10);

	// Belly
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawCircle(wxPoint(50, 200), 100);

	// Text
	dc.DrawText(m_label->GetLineText(0), wxPoint(300, 300));

	// Onion
	dc.DrawBitmap(m_onion, wxPoint(200, 100));
}

void MonkeyMainFrame::saveImage(wxCommandEvent& event)
{

}

void MonkeyMainFrame::toggleOnion(wxCommandEvent& event)
{
	// TODO: Implement toggleBanana
}

void MonkeyMainFrame::handleHandPositionChange(wxScrollEvent& event)
{
	wxString msg;
	msg.Printf(wxT("Position: %d"), event.GetPosition());
	wxMessageBox(msg);
}

void MonkeyMainFrame::chooseColor(wxCommandEvent& event)
{

}

void MonkeyMainFrame::changeLabel(wxCommandEvent& event)
{
	// TODO: Implement changeLabel
}

void MonkeyMainFrame::changeSymbol(wxCommandEvent& event)
{
	// TODO: Implement changeSymbol
}
