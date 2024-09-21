#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include"MainWindow.h"
#include "wx/wx.h"
#include <vector>

class MainWindow;
class App;
struct gameSetting;

// Declaration of the DrawingPanel class, inheriting from wxPanel
class DrawingPanel : public wxPanel {
public:
    // Constructor for DrawingPanel, taking a parent window as an argument
    DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard, gameSetting* settings);

    // Destructor for DrawingPanel
    ~DrawingPanel();

    // custom set size method used with the resize method of mainwindow 
    void setSize(wxSize& size);

    // Sets a new grid set
    void SetGridSize(int newGrid);

    // Event table declaration
    wxDECLARE_EVENT_TABLE();
    
private:
    std::vector<std::vector<bool>>& drawingBoard;
    int cellHeight;
    int cellWidth;
    MainWindow* mainWindow;
    gameSetting* gameSettings;
    

    // Finds where the mouse is locatied 
    void onClick(wxMouseEvent& event);

    // Calulates the cell height and width
    void Cell();
    
    // Handles all the painting in the program 
	void OnPaint(wxPaintEvent& event);
};

#endif // DRAWINGPANEL_H