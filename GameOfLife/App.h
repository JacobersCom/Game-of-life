#pragma once

#include "wx/wx.h"
#include "MainWindow.h"


class App : public wxApp
{
private:
	MainWindow* mainWindow;

public:
	App();
	~App();
	
	// Override of the OnInit method, called on application startup
	virtual bool OnInit();
};
