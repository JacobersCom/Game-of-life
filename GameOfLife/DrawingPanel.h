#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include "wx/wx.h"

// Declaration of the DrawingPanel class, inheriting from wxPanel
class DrawingPanel : public wxPanel {
public:
    // Constructor for DrawingPanel, taking a parent window as an argument
    DrawingPanel(wxWindow* parent);

    // Destructor for DrawingPanel
    ~DrawingPanel();

	void OnPaint(wxPaintEvent& event);
    void setSize(wxSize& size);

private:
    int gridSize = 15;
};

#endif // DRAWINGPANEL_H