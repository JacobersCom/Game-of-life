#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include"MainWindow.h"
#include "wx/wx.h"
#include <vector>
class MainWindow;
// Declaration of the DrawingPanel class, inheriting from wxPanel
class DrawingPanel : public wxPanel {
public:
    // Constructor for DrawingPanel, taking a parent window as an argument
    DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard);

    // Destructor for DrawingPanel
    ~DrawingPanel();

    
	void OnPaint(wxPaintEvent& event);
    void setSize(wxSize& size);
    void SetGridSize(int newGird);
    void onClick(wxMouseEvent& event);
    
private:
    int gridSize = 15;
    std::vector<std::vector<bool>>& drawingBoard;
    
};

#endif // DRAWINGPANEL_H