#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
public:

	MainWindow();
	~MainWindow();

private: 
	DrawingPanel* draw; 
};
