#include "App.h"

wxIMPLEMENT_APP(App);

App::App()
{}

App::~App() 
{}


bool App::OnInit() {
	main = new MainWindow;
	main->Show();
	return true;
}