#pragma once
#include "wx/wx.h"
#include "wx/spinctrl.h"
#include <iostream>
#include <fstream>


struct gameSetting {
public:
	int gridSize;
	int time = 5;
	bool neighbor;
	
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
	void SetGridSize(int newgrid)
	{
		gridSize = newgrid;
	}
	int GetGridSize() const {
		
		return gridSize;
	}
	int GetInterval() const {
		
		return time;
	}
	void SetInterval(int newInterval){
		
		time = newInterval;
	}
	void LoadingData()
	{
		std::ifstream file("Save.bin", std::ios::binary | std::ios::in);
		if (file.is_open())
		{
			file.read((char*)this, sizeof(gameSetting));
		}
			file.close();
	}
	void SaveData()
	{
		std::ofstream file("Save.bin", std::ios::binary | std::ios::out);
		if (file.is_open())
		{
			file.write((char*)this, sizeof(gameSetting));
		}
			file.close();
	}
};