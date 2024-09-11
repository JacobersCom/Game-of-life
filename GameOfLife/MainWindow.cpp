#include "MainWindow.h"

// Definition of the MainWindow constructor
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 600)) { // Initialize the base wxFrame class with position and size
    
    // Initialize the DrawingPanel with "this" as the parent
   drawing = new DrawingPanel(this, gameBoard); 
    
    this->Bind(wxEVT_SIZE, &MainWindow::ReSize, this);
    
    GridInitializtion(grid);

    
}

// Definition of the MainWindow destructor
MainWindow::~MainWindow() {
    // Empty destructor
}

void MainWindow::ReSize(wxSizeEvent& event)
{
    // Saving window size as a wxSize object
    wxSize size(800,600); 

    // Calling the setSize method from the drawing panel class
    drawing->setSize(size); 

    // Used to skip any another function when resizing the window
    event.Skip(); 

}

void MainWindow::GridInitializtion(int gridSize)
{

    for (size_t i = 0; i < gameBoard.size(); i++)
    {
        gameBoard[i].resize(gridSize); 
    }
    drawing->SetGridSize(gridSize);
}


