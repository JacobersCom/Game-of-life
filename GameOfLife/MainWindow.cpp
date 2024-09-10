#include "MainWindow.h"

// Definition of the MainWindow constructor
MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 600)) { // Initialize the base wxFrame class with position and size
    drawingPanel = new DrawingPanel(this); // Instantiate the DrawingPanel with this as the parent
    this->Bind(wxEVT_SIZE, &MainWindow::ReSize, this);
}

// Definition of the MainWindow destructor
MainWindow::~MainWindow() {
    // Empty destructor
}

void MainWindow::ReSize(wxSizeEvent& event)
{
    wxSize size(800,600); // Saving window size as a wxSize object
    drawingPanel->setSize(size); // Calling the setSize method from the drawing panel class
    event.Skip(); // Used to skip any another function when resizing the window
}


