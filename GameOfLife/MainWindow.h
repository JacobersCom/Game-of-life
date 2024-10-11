#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "DrawingPanel.h"
#include "Dialog_UI.h"
#include "GameSettings.h"
#include <vector>
#include <cstdlib>
#include "wx/numdlg.h"
#include  "wx/filedlg.h"


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
  void SaveGameButton(wxCommandEvent& event);
  void DefaultButton(wxCommandEvent& event);
  void NeighborCheck(wxCommandEvent& event);
  void OnRandomize(wxCommandEvent& event);
  void OnRandomizeWithSeed(wxCommandEvent& event);
  void RandomizeGrid(int seed);
  void OpenFileButton(wxCommandEvent& event);
  void ExitButton(wxCommandEvent& event);
  void SaveAsButton(wxCommandEvent& event);
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
    std::vector<std::vector<int>> neighbor;
    std::vector<std::vector<bool>> gameBoard;
    
    int Gen; 
    int livCells; 
    
    wxMenuBar* mainBar;
    
    wxMenu* fileMenu;
    wxMenuItem* New;
    wxMenuItem* Open;
    wxMenuItem* Save;
    wxMenuItem* saveAs;
    wxMenuItem* Exit;
    
    wxMenu* view;
    wxMenuItem* neighborcount;
    
    wxMenu* randomizer;
    wxMenuItem* RandSeed;
    wxMenuItem* Randomize;
    
    wxStatusBar* statusBar;
    
    wxToolBar* toolBar;
    
    wxTimer* timer;
    
    wxMenu* optionsBar;
    wxMenuItem* defaultBar;
  
   
    
    gameSetting setting;
    DrawingPanel* drawing; 
    Dialog_UI* ui;

    wxColor color;
    wxColor whiteColor;

    
};

#endif // MAINWINDOW_H