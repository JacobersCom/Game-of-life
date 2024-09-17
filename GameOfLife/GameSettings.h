#pragma once
#include "wx/wx.h"

struct gameSetting {
public:
	int gridSize = 30;
	int time = 50; 
	
	unsigned int Red = 128;
	unsigned int Green = 128;
	unsigned int Blue = 128;
	unsigned int Alpha = 255;
	unsigned int redDead = 255;
	unsigned int greenDead = 255;
	unsigned int blueDead = 255;
	unsigned int alphaDead = 255;

	void setColor(wxColor color) {
		Red = color.GetRed();
		Green = color.GetGreen();
		Blue = color.GetBlue();
	}
	wxColor GetColor() {
		wxColor color(Red, Green, Blue, Alpha);
		return color;
	}
	void SetDeadColor(wxColor color) {
		redDead = color.GetRed();
		greenDead = color.GetGreen();
		blueDead = color.GetBlue();
	}
	wxColor GetDeadColor() {
		wxColor color(redDead, greenDead, blueDead, alphaDead);
		return color;
	}

	int GetGridSize() {
		
		return gridSize;
	}
};