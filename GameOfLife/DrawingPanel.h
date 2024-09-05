#pragma once
#include "wx/wx.h"
#include "MainWindow.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

class DrawingPanel : public wxPanel
{
public:
	
	DrawingPanel(MainWindow* parent);
	~DrawingPanel();

	void onPaint(wxPaintEvent& event);

private:
	DrawingPanel* draw;
};

