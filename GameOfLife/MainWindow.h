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
  
  // Giving text to the status bar
  void StatusBarText();

  //Button methods
  void PlayButton(wxCommandEvent& event);
  void TrashButton(wxCommandEvent& event);
  void PauseButton(wxCommandEvent& event);
  void NextButton(wxCommandEvent& event);

  //Calulating the amount of people around to see if the gen will live or die
  int NeighborCounter(int row, int col);

  // Calls the method above and adds to the gen memeber field
  void NextGen();

  //Adds a timer to my play button event
  void Timer(wxTimerEvent& event);

  //Helper method for my tool bar
  void addToolFields(int ID, std::string name, wxBitmap icon);

  //Event table declaration 
  wxDECLARE_EVENT_TABLE();


private:
    // Pointer to the DrawingPanel instance
    DrawingPanel* drawing;
    int gridSize = 15; 
    std::vector<std::vector<bool>> gameBoard;
    int Gen; 
    int livCells; 
    wxStatusBar* statusBar;
    wxToolBar* toolBar;
    wxTimer* timer;
    int time = 50;
};

#endif // MAINWINDOW_H