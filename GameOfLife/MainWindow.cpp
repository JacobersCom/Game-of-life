#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "trash.xpm"
#include "next.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::ReSize)
EVT_MENU(10000, PlayButton)
EVT_MENU(10001, PauseButton)
EVT_MENU(10002, TrashButton)
EVT_MENU(10003, NextButton)
wxEND_EVENT_TABLE()

// Definition of the MainWindow constructor
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 600)), Gen(0), livCells(0) { // Initialize the base wxFrame class with position and size
    statusBar = CreateStatusBar();
    
    StatusBarText();
    
    toolBar = CreateToolBar();

    //Bitmap for the playerIcon that takes the C style char array
    wxBitmap playicon(play_xpm);
    //A helper method that takes a int string and wxBitmap and adds the Play button to the tool bar
    addToolFields(10000, "Play", playicon);
    wxBitmap pauseicon(pause_xpm);
    addToolFields(10001, "Pause", pauseicon);;
    wxBitmap trashicon(trash_xpm);
    addToolFields(10002, "Trash", trashicon);
    wxBitmap nexticon(next_xpm);
    addToolFields(10003, "Next", nexticon);


    toolBar->Realize();

    // Initialize the DrawingPanel with "this" as the parent
    drawing = new DrawingPanel(this, gameBoard); 
    
    GridInitializtion();

    this->Layout();
}

// Definition of the MainWindow destructor
MainWindow::~MainWindow() {
   
    delete drawing;
}

void MainWindow::ReSize(wxSizeEvent& event)
{
    //Checking if drawing is not nullptr
    if (drawing != nullptr)
    {
        //Initialization for the grid
        GridInitializtion();

        // Saving window size as a wxSize object
        wxSize size = this->GetClientSize();

        //Taking the DrawingPanel pointer and pointer to the setSize method and passing in the wxSize object
        drawing->setSize(size);
    }

    // Allows another functions to handle the event
    event.Skip(); 

}

void MainWindow::GridInitializtion()
{
    wxSize size = this->GetClientSize();
    
    gameBoard.resize(gridSize);

    for (size_t i = 0; i < gameBoard.size(); i++)
    {
        gameBoard[i].resize(gridSize);
    }
    drawing->SetGridSize(gridSize);
}

void MainWindow::StatusBarText()
{
    std::string bar = "   \t\t\t\t\t\t\t\t\t\t\t\t\tGeneration: " + std::to_string(Gen) + "\t\t\t\t|\t\t\t\t" + std::to_string(livCells) + " :Living";
    statusBar->SetStatusText(bar);
}

void MainWindow::PlayButton(wxCommandEvent& event)
{
    NextGen();
}

void MainWindow::TrashButton(wxCommandEvent& event)
{
}

void MainWindow::PauseButton(wxCommandEvent& event)
{
}

void MainWindow::NextButton(wxCommandEvent& event)
{
}

int MainWindow::NeighborCounter(int row, int col)
{
    int Livecount = 0;

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            
            int mRow = row + i;
            int mCol = col + j;

            if (mRow >= 0 && mRow < gridSize && mCol >= 0 && mCol < gridSize)
            {
                if (gameBoard[mRow][mCol] == true)
                {
                    Livecount += 1;
                }
            }
        }
    }
    
    return Livecount;
}

void MainWindow::NextGen()
{
    std::vector<std::vector<bool>> sandbox;

    sandbox.resize(gridSize);
    for (int i = 0; i < sandbox.size(); i++)
    {
        sandbox[i].resize(gridSize);
    }
    
    livCells = 0;

    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            int neighbors = NeighborCounter(row, col);
            
            if (gameBoard[row][col] == true)
            {
                if (neighbors < 2 || neighbors > 3)
                {
                    sandbox[row][col] = false;

                }
                else
                {
                    sandbox[row][col] = true;
                    ++livCells;

                }
                   
            }
            else if (neighbors == 3)
            {
                sandbox[row][col] = true;
                ++livCells;
            }
            else
            {
                sandbox[row][col] = false;
            }
        }
    }
    
    gameBoard.swap(sandbox);

    Gen += 1;
    UpdateStatusBar(Gen, livCells);

    Refresh();
   
}

void MainWindow::addToolFields(int ID, std::string name, wxBitmap icon)
{
    toolBar->AddTool(ID, name, icon);
}

void MainWindow::UpdateStatusBar(int alive, int gen)
{  
    livCells += alive;
    
    StatusBarText();
}



