#include "Dialog_UI.h"
wxBEGIN_EVENT_TABLE(Dialog_UI, wxDialog)
EVT_BUTTON(wxID_OK, Dialog_UI::okButtomClicked)
EVT_BUTTON(wxID_CANCEL, Dialog_UI::cancelButtomClicked)
wxEND_EVENT_TABLE()

Dialog_UI::Dialog_UI(wxWindow* parent, gameSetting* settings) :wxDialog(parent, wxID_ANY, "Settings", wxPoint(725,300), wxSize(225, 265)), setting(settings)
{
	mainBox = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mainBox);

	gridBox = new wxBoxSizer(wxHORIZONTAL);
	gridSizeLabel = new wxStaticText(this, wxID_ANY, "Grid Size");
	gridSizeSpin = new wxSpinCtrl(this, 10001, "gridSize", wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 5, 100, 5);

	intervalBox = new wxBoxSizer(wxHORIZONTAL);
	intervalLabel = new wxStaticText(this, wxID_ANY, "Time Interval");
	intervalSpin = new wxSpinCtrl(this, 10002);
	
	aliveColor = new wxColourPickerCtrl(this, 10002, setting->GetColor());
	aliveColorLabel = new wxStaticText(this, wxID_ANY, "Alive Color");
	deadColor = new wxColourPickerCtrl(this, 10003, setting->GetDeadColor());
	deadColorLabel = new wxStaticText(this, wxID_ANY, "Dead Color");
	sizer = (CreateButtonSizer(wxOK | wxCANCEL));
	
	mainBox->Add(gridBox);
	mainBox->Add(gridSizeLabel, 0, wxLEFT, 3);
	mainBox->Add(gridSizeSpin, 0, wxALL, 3);
	mainBox->Add(intervalBox);
	mainBox->Add(intervalLabel, 0, wxLEFT, 3);
	mainBox->Add(intervalSpin, 0, wxALL, 3);
	mainBox->Add(aliveColorLabel, 0, wxLEFT, 3);
	mainBox->Add(aliveColor, 0, wxALL, 3);
	mainBox->Add(deadColorLabel, 0, wxLEFT, 3);
	mainBox->Add(deadColor, 0, wxALL, 3);
	mainBox->Add(sizer, 0, wxUP, 3);
}

Dialog_UI::~Dialog_UI()
{
}

void Dialog_UI::okButtomClicked(wxCommandEvent& event)
{

	if (wxOK)
	{
		setting->gridSize = gridSizeSpin->GetValue();
		setting->time = intervalSpin->GetValue();
		setting->setColor(aliveColor->GetColour());
		setting->SetDeadColor(deadColor->GetColour());

		EndModal(wxOK);
	}
	
}

void Dialog_UI::cancelButtomClicked(wxCommandEvent& event)
{
	if (wxCANCEL)
	{
		EndModal(wxCANCEL);
	}
}





