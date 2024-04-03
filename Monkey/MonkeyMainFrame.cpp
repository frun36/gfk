#include "MonkeyMainFrame.h"

MonkeyMainFrame::MonkeyMainFrame(wxWindow* parent)
	:
	MainFrame(parent)
{
	m_handControl->SetRange(100);
	m_handControl->SetThumbPosition(50);
	m_onionImg.AddHandler(new wxPNGHandler);
	m_onionImg.LoadFile("onion.png", wxBITMAP_TYPE_PNG);
	m_onionBitmap = wxBitmap(m_onionImg);
	m_hasOnion = m_onion->IsChecked();
	setOnionPosition(static_cast<double>(m_handControl->GetThumbPosition()) / m_handControl->GetRange());
}

void MonkeyMainFrame::onBgErase(wxEraseEvent& event)
{
	event.Skip(false);
}

void MonkeyMainFrame::repaint(wxPaintEvent& event)
{
	wxClientDC dc(m_canvas);
	dc.SetDeviceOrigin(100, 100);
	dc.SetPen(*wxTRANSPARENT_PEN);

	m_canvas->ClearBackground();

	// Head
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawRectangle(0, 0, 100, 120);
	dc.DrawRectangle(15, -40, 10, 40);
	dc.DrawRectangle(75, -40, 10, 40);

	// Mouth
	if (m_hasOnion) {
		dc.SetBrush(*wxWHITE_BRUSH);
		dc.DrawCircle(wxPoint(50, 70), 30);
		dc.SetBrush(*wxGREEN_BRUSH);
		dc.DrawCircle(wxPoint(50, 50), 40);
	} else {
		dc.SetBrush(*wxWHITE_BRUSH);
		dc.DrawCircle(wxPoint(50, 105), 30);
		dc.SetBrush(*wxGREEN_BRUSH);
		dc.DrawCircle(wxPoint(50, 125), 40);
	}
	
	// Eyes
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.DrawCircle(wxPoint(30, 30), 10);
	dc.DrawCircle(wxPoint(70, 30), 10);

	// Belly
	dc.SetBrush(*wxGREEN_BRUSH);
	dc.DrawCircle(wxPoint(50, 200), 100);

	// Arm
	dc.SetPen(*wxGREEN_PEN);
	dc.DrawLine(wxPoint(50, 200), wxPoint(m_onionPosition.x + m_onionBitmap.GetWidth(), m_onionPosition.y + m_onionBitmap.GetHeight()));

	// Text
	dc.DrawText(m_label->GetLineText(0), wxPoint(300, 300));

	// Onion
	if (m_hasOnion)
		dc.DrawBitmap(m_onionBitmap, m_onionPosition);
}

void MonkeyMainFrame::saveImage(wxCommandEvent& event)
{
	// TODO: Implement saveImage
}

void MonkeyMainFrame::toggleOnion(wxCommandEvent& event)
{
	m_hasOnion = event.IsChecked();
	Refresh();
}

void MonkeyMainFrame::handleHandPositionChange(wxScrollEvent& event)
{
	m_handDisplay->SetValue(event.GetPosition());
	setOnionPosition(static_cast<double>(m_handControl->GetThumbPosition()) / m_handControl->GetRange());
	Refresh();
}

void MonkeyMainFrame::chooseColor(wxCommandEvent& event)
{
	// TODO: Implement chooseColor
}

void MonkeyMainFrame::changeLabel(wxCommandEvent& event)
{
	Refresh();
}

void MonkeyMainFrame::changeSymbol(wxCommandEvent& event)
{
	// TODO: Implement changeSymbol
}
