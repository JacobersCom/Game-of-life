#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

// Definition of the OnInit method
bool App::OnInit() {
    mainWindow = new MainWindow(); // Instantiate the MainWindow
    mainWindow->Show(true); // Show the main window
    return true; // Return true to indicate successful initialization
}