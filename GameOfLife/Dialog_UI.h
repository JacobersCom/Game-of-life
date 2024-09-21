#pragma once
#include "wx/wx.h"
#include "MainWindow.h"
#include "GameSettings.h"
#include "wx/spinctrl.h"
#include "wx/clrpicker.h"

class Dialog_UI : public wxDialog
{
public:

	Dialog_UI(wxWindow* parent, gameSetting* settings);
	~Dialog_UI();
	void okButtomClicked(wxCommandEvent& event);
	void cancelButtomClicked(wxCommandEvent& event);
	

	wxDECLARE_EVENT_TABLE();

private:
	
	gameSetting* setting;
	wxBoxSizer* mainBox;
	wxBoxSizer* intervalBox;
	wxBoxSizer* gridBox;
	wxStaticText* intervalLabel;
	wxStaticText* gridSizeLabel;
	wxStaticText* aliveColorLabel;
	wxStaticText* deadColorLabel;
	wxSpinCtrl* gridSizeSpin;
	wxSpinCtrl* intervalSpin;
	wxColourPickerCtrl* aliveColor;
	wxColourPickerCtrl* deadColor;
	wxSizer* Button; 
	
};

