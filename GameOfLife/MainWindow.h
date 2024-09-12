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
 
  //Update status bar to count gen and LivCell count
  void UpdateStatusBar(int alive);
  void StatusBarText();

  wxDECLARE_EVENT_TABLE();


private:
    // Pointer to the DrawingPanel instance
    DrawingPanel* drawing;
    int gridSize = 15; 
    std::vector<std::vector<bool>> gameBoard;
    int Gen; 
    int livCells; 
    wxStatusBar* statusBar;
   
    
};

#endif // MAINWINDOW_H