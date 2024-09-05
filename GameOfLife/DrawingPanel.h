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

private:
    // Declaration of the OnPaint method, which will handle paint events
    void OnPaint(wxPaintEvent& event);
};

#endif // DRAWINGPANEL_H