#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "DrawingPanel.h"
#include "Dialog_UI.h"
#include "GameSettings.h"
#include <vector>


class DrawingPanel;
struct gameSetting;
class Dialog_UI;

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
  void SettingsButton(wxCommandEvent& event);
  void SaveGame(wxCommandEvent& event);
  void Default(wxCommandEvent& event);
  void NeighborCheck(wxCommandEvent& event);

  //Calulating the amount of people around to see if the gen will live or die
  int NeighborCounter(int row, int col);

  // Calls the method above and adds to the gen memeber field
  void NextGen();

  //Adds a timer to my play button event
  void Timer(wxTimerEvent& event);

  //Helper method for my tool bar
  void addToolFields(int ID, std::string name, wxBitmapBundle icon);

  //Event table declaration 
  wxDECLARE_EVENT_TABLE();


private:
    DrawingPanel* drawing; 
    std::vector<std::vector<int>> neighbor;
    std::vector<std::vector<bool>> gameBoard;
    int Gen; 
    int livCells; 
    wxStatusBar* statusBar;
    wxToolBar* toolBar;
    wxTimer* timer;
    wxMenu* settingsBar;
    wxMenu* saveBar;
    wxMenu* defaultBar;
    wxMenu* view;
    wxMenuBar* mainBar;
    wxMenuItem* item;
    gameSetting setting;
    Dialog_UI* ui;
    wxColor color;
    wxColor whiteColor;

    
};

#endif // MAINWINDOW_H