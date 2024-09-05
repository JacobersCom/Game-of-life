#include "MainWindow.h"

// Definition of the MainWindow constructor
MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 600)) { // Initialize the base wxFrame class with position and size
    drawingPanel = new DrawingPanel(this); // Instantiate the DrawingPanel with this as the parent
}

// Definition of the MainWindow destructor
MainWindow::~MainWindow() {
    // Empty destructor
}