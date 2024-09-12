#include "MainWindow.h"
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::ReSize)
wxEND_EVENT_TABLE()

// Definition of the MainWindow constructor
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 600)), Gen(0), livCells(0) { // Initialize the base wxFrame class with position and size
    statusBar = CreateStatusBar();
    StatusBarText();
   
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

    GridInitializtion();

    // Saving window size as a wxSize object
    wxSize size = this->GetClientSize();

    // Calling the setSize method from the drawing panel class
    drawing->setSize(size); 

    // Used to skip any another function when resizing the window
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

void MainWindow::UpdateStatusBar(int alive)
{  
    livCells += alive;
    StatusBarText();
}



