#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include"MainWindow.h"
#include "wx/wx.h"
#include <vector>
class MainWindow;
class App;

// Declaration of the DrawingPanel class, inheriting from wxPanel
class DrawingPanel : public wxPanel {
public:
    // Constructor for DrawingPanel, taking a parent window as an argument
    DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard);

    // Destructor for DrawingPanel
    ~DrawingPanel();

    void setSize(wxSize& size);
    void SetGridSize(int newGrid);

    wxDECLARE_EVENT_TABLE();
    
private:
    int gridSize;
    std::vector<std::vector<bool>>& drawingBoard;
    int cellHeight;
    int cellWidth;
    MainWindow* mainWindow;

    void onClick(wxMouseEvent& event);
    void Cell();
	void OnPaint(wxPaintEvent& event);
};

#endif // DRAWINGPANEL_H