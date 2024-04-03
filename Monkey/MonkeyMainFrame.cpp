#include "MonkeyMainFrame.h"

MonkeyMainFrame::MonkeyMainFrame(wxWindow* parent)
	:
	MainFrame(parent)
{
	m_handControl->SetRange(100);
	m_handControl->SetThumbPosition(50);
	m_handControl->Disable();
	m_onionImg.AddHandler(new wxPNGHandler);
	m_onionImg.AddHandler(new wxJPEGHandler);
	m_onionImg.LoadFile("onion.png", wxBITMAP_TYPE_PNG);
	m_onionBitmap = wxBitmap(m_onionImg);
	m_hasOnion = m_onion->IsChecked();
	setOnionPosition(static_cast<double>(m_handControl->GetThumbPosition()) / m_handControl->GetRange());
	m_symbol = STAR;

	m_starVertices[0] = wxPoint(50, 0);
	m_starVertices[1] = wxPoint(25, 90);
	m_starVertices[2] = wxPoint(100, 30);
	m_starVertices[3] = wxPoint(0, 30);
	m_starVertices[4] = wxPoint(75, 90);
	m_starVertices[5] = wxPoint(50, 0);

	m_starBrush = *wxBLACK_BRUSH;
}

void MonkeyMainFrame::onBgErase(wxEraseEvent& event)
{
	event.Skip(false);
}

void MonkeyMainFrame::repaint(wxPaintEvent& event)
{
	wxClientDC dc(m_canvas);
	dc.SetDeviceOrigin(m_canvas->GetSize().x * 0.5 - 50, m_canvas->GetSize().y * 0.5 - 200);
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
	}
	else {
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
	dc.SetPen(*wxTRANSPARENT_PEN);

	// Text
	dc.SetTextForeground(*wxBLACK);
	wxFont font(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);
	dc.SetFont(font);

	dc.DrawText(m_label->GetLineText(0), wxPoint(200, 300));

	wxFont font2(24, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false);
	dc.SetFont(font2);
	dc.DrawRotatedText(m_label->GetLineText(0), -200, 200, 90);

	// Onion
	if (m_hasOnion)
		dc.DrawBitmap(m_onionBitmap, m_onionPosition);

	// Symbol
	switch (m_symbol) {
	case SUN:
		dc.SetBrush(*wxYELLOW_BRUSH);
		dc.DrawCircle(wxPoint(250, 0), 40);
		break;
	case STAR:
		dc.SetBrush(m_starBrush);
		dc.DrawPolygon(6, m_starVertices, 200, -50);
		break;
	case MOON:
		dc.SetBrush(*wxGREY_BRUSH);
		dc.DrawCircle(wxPoint(250, 0), 40);
		dc.SetBrush(*wxWHITE_BRUSH);
		dc.DrawCircle(wxPoint(230, -20), 40);
		break;
	}
}

void MonkeyMainFrame::resize(wxSizeEvent& event)
{
	Refresh();
}

void MonkeyMainFrame::saveImage(wxCommandEvent& event)
{
	wxFileDialog dialog(this, "Save Image", "", "", "JPG files (*.jpg)|*.jpg", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (dialog.ShowModal() == wxID_OK) {
		wxString filePath = dialog.GetPath();

		wxBitmap bitmap(m_canvas->GetSize());
		wxMemoryDC memDC(bitmap);
		wxClientDC dc(m_canvas);
		memDC.Blit(0, 0, m_canvas->GetSize().GetWidth(), m_canvas->GetSize().GetHeight(), &dc, 0, 0);

		bitmap.SaveFile(filePath, wxBITMAP_TYPE_JPEG);
	}
}

void MonkeyMainFrame::toggleOnion(wxCommandEvent& event)
{
	m_hasOnion = event.IsChecked();
	if (event.IsChecked()) {
		m_handControl->Enable();
	}
	else {
		m_handControl->Disable();
	}
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
	wxColourDialog dialog(this);
	if (dialog.ShowModal() == wxID_OK) {
		wxColourData data = dialog.GetColourData();
		wxColour color = data.GetColour();
		m_starBrush = wxBrush(color); // Update star color
		Refresh(); // Redraw the panel to apply the new color
	}
}

void MonkeyMainFrame::changeLabel(wxCommandEvent& event)
{
	Refresh();
}

void MonkeyMainFrame::changeSymbol(wxCommandEvent& event)
{
	m_symbol = static_cast<MonkeyMainFrame::Symbol>(event.GetInt());
	Refresh();
}
