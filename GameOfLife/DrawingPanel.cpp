#include "DrawingPanel.h"



DrawingPanel::DrawingPanel(MainWindow* parent)
	: wxPanel(parent, wxID_ANY)
{   
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
	this->Bind(wxEVT_PAINT, &DrawingPanel::onPaint, this);
}

DrawingPanel::~DrawingPanel()
{
}

void DrawingPanel::onPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc (this);

	dc.Clear();

	wxGraphicsContext* gcPtr = wxGraphicsContext::Create(dc);
	
	if (!gcPtr) { return; }
	gcPtr->SetPen(*wxBLACK);
	gcPtr->SetBrush(*wxWHITE);
	gcPtr->DrawRectangle(0,0,200,200);

	delete gcPtr;
}
