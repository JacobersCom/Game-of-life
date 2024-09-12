#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>

class DrawingPanel;
// Declaration of the MainWindow class, inheriting from wxFrame
class MainWindow : public wxFrame {
public:
    // Constructor for MainWindow
    MainWindow();

    // Destructor for MainWindow
    ~MainWindow();

    // To Resize the window without jiddering
    void ReSize(wxSizeEvent& event);


    // to initialize the gird vector
  void GridInitializtion(); 
 

  wxDECLARE_EVENT_TABLE();

private:
    // Pointer to the DrawingPanel instance
    DrawingPanel* drawing;
    int gridSize = 15; 
    std::vector<std::vector<bool>> gameBoard;
    
};

#endif // MAINWINDOW_H