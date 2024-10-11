#include "MainWindow.h"
#include "play.xpm"
#include "pause.xpm"
#include "trash.xpm"
#include "next.xpm"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::ReSize)
EVT_MENU(10000, PlayButton)
EVT_MENU(10001, PauseButton)
EVT_MENU(10002, TrashButton)
EVT_MENU(10003, NextButton)
EVT_TIMER(10004, MainWindow::Timer)
EVT_MENU(10005, MainWindow::SettingsButton)
EVT_MENU(10006, MainWindow::SaveGameButton)
EVT_MENU(10007, MainWindow::DefaultButton)
EVT_MENU(10008, MainWindow::NeighborCheck)
EVT_MENU(10009, MainWindow::OnRandomize)
EVT_MENU(10010, MainWindow::OnRandomizeWithSeed)
EVT_MENU(10015, MainWindow::ExitButton)
EVT_MENU(wxID_OPEN, MainWindow::OpenFileButton)
EVT_MENU(10014, MainWindow::SaveAsButton)
wxEND_EVENT_TABLE()

// Definition of the MainWindow constructor
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 600)), Gen(0), livCells(0){ // Initialize the base wxFrame class with position and size
    
    setting.LoadingData();
    
    mainBar = new wxMenuBar();
    
    fileMenu = new wxMenu();
    
    // Redo with wxprebuild IDs EX:: wxID_SAVE
    New = new wxMenuItem(fileMenu, 10011, "New file", wxEmptyString);
    Open = new wxMenuItem(fileMenu, wxID_OPEN, "Open file", wxEmptyString);
    Save = new wxMenuItem(fileMenu, 10006, "Save", wxEmptyString);
    saveAs = new wxMenuItem(fileMenu, 10014, "Save As", wxEmptyString);
    Exit = new wxMenuItem(fileMenu, 10015, "Exit", wxEmptyString);
    fileMenu->Append(New);
    fileMenu->Append(Open);
    fileMenu->Append(Save);
    fileMenu->Append(saveAs);
    fileMenu->Append(Exit);
    mainBar->Append(fileMenu, "File");

    view = new wxMenu();
    neighborcount = new wxMenuItem(view, 10008, "Neighbor Count", wxEmptyString, wxITEM_CHECK);
    view->Append(neighborcount);
    mainBar->Append(view, "View");
    neighborcount->SetCheckable(true);
    
    randomizer = new wxMenu();
    Randomize = new wxMenuItem(randomizer, 10009, "Randomize(time)", wxEmptyString, wxITEM_CHECK);
    RandSeed = new wxMenuItem(randomizer, 10010, "Randomize(seed)", wxEmptyString, wxITEM_CHECK);
    Randomize->SetCheckable(true);
    RandSeed->SetCheckable(true);
    randomizer->Append(Randomize);
    randomizer->Append(RandSeed);
    mainBar->Append(randomizer, "Randomizer");
    
    
    optionsBar = new wxMenu();
    optionsBar->Append(10005, "Settings");
    defaultBar = new wxMenuItem(optionsBar, 10007, "Default Settings", wxEmptyString);
    optionsBar->Append(defaultBar);
    mainBar->Append(optionsBar, "Options");
    
    SetMenuBar(mainBar);
    
    // Creating my status bar
    statusBar = CreateStatusBar();
    
    // Calling the method for my bar text
    StatusBarText();
    
    // Creating my tool bar
    toolBar = CreateToolBar();

    //Initialzing the wxTimer pointer
    timer = new wxTimer(this, 10004);
   
    //A helper method that takes a int string and wxBitmap and adds the Play button to the tool bar
    wxBitmapBundle playicon(play_xpm) ,pauseicon(pause_xpm), trashicon(trash_xpm), nexticon(next_xpm);
    addToolFields(10000, "Play", playicon);
    addToolFields(10001, "Pause", pauseicon);;
    addToolFields(10002, "Trash", trashicon);
    addToolFields(10003, "Next", nexticon);

    //Used to finalizes the placement of the tool bar 
    toolBar->Realize();

    // Initialize the DrawingPanel with "this" as the parent
    drawing = new DrawingPanel(this, gameBoard, &setting); 

   
    GridInitializtion();

    this->Layout();
    ui = new Dialog_UI(this, &setting);
   

}

// Definition of the MainWindow destructor
MainWindow::~MainWindow() {
   
    //Clean up;
    delete drawing;
    delete timer;
    
    
}

void MainWindow::ReSize(wxSizeEvent& event)
{
    //Checking if drawing is not nullptr
    if (drawing != nullptr)
    {
        //Initialization for the grid
        GridInitializtion();

        // Saving window size as a wxSize object
        wxSize size = this->GetClientSize();

        //Taking the DrawingPanel pointer and pointer to the setSize method and passing in the wxSize object
        drawing->setSize(size);
    }

    // Allows another functions to handle the event
    event.Skip(); 
    
}

void MainWindow::GridInitializtion()
{
    // Getting the ClientSize
    /*wxSize size = this->GetClientSize();*/
    
    // Making the vector the same size as the grid(15)
    neighbor.resize(setting.gridSize);
    for (size_t i = 0; i < neighbor.size(); i++)
    {
        neighbor[i].resize(setting.gridSize, 0);
    }


    //resizing the vectors inside the vector
    gameBoard.resize(setting.gridSize);
    for (size_t i = 0; i < gameBoard.size(); i++)
    {
        gameBoard[i].resize(setting.gridSize);
       
    }

    //Calling the set grid size from drawing panel and passing in the gridsize 
   /* drawing->SetGridSize(setting.gridSize);*/
   
}


void MainWindow::StatusBarText()
{

    std::string bar = "   \t\t\t\t\t\t\t\t\t\t\t\t\tGeneration: " + std::to_string(Gen) + "\t\t\t\t|\t\t\t\t" + std::to_string(livCells) + " :Living";
    statusBar->SetStatusText(bar);
    
}
void MainWindow::UpdateStatusBar(int alive)
{  
    //Adding the alive cells to livcells
    livCells += alive;
   
    // updating the test for the bar
    StatusBarText();
    
}

void MainWindow::PlayButton(wxCommandEvent& event)
{
    //timer is pointer of wxtime pointer to the start method to start a timer for 50 milisecs
    timer->Start(setting.time);
}
void MainWindow::TrashButton(wxCommandEvent& event)
{
    // Nested for loop resetting the vector of vectors to false
   /* for (int i = 0; i < gameBoard.size(); i++)
    {
        for (int j = 0; j < gameBoard.size(); j++)
        {
            gameBoard[i][j] = false;
        }
    }*/

    for (auto& row : gameBoard) {
        for (auto& col : gameBoard) {
            std::fill(row.begin(), row.end(), false);
            std::fill(col.begin(), col.end(), false);
        }
    }
    
    // setting Gen and LivCells back to 0
    Gen = 0;
    livCells = 0;

    // Updating the statusbar and only passing in livcells being within the method it already tracks the gen
    UpdateStatusBar(livCells);

    // Stopping the timer if its going
    timer->Stop();

    //Refreshing the drawingpanel
    Refresh();
}
void MainWindow::PauseButton(wxCommandEvent& event)
{
    //Stops timer in play method
    timer->Stop();
}
void MainWindow::NextButton(wxCommandEvent& event)
{
    NextGen();
}
void MainWindow::SettingsButton(wxCommandEvent& event)
{
    ui = new Dialog_UI(this, &setting);
    
    if (ui->ShowModal() == wxOK)
    {
        GridInitializtion();
        drawing->Refresh();
    }
    else if (wxCANCEL)
    {
        return;
    }
}
void MainWindow::DefaultButton(wxCommandEvent& event)
{
    GridInitializtion();
    setting.SetGridSize(15);
    setting.SetInterval(5);
    color = *wxLIGHT_GREY;
    setting.setColor(color);
    whiteColor = *wxWHITE;
    setting.SetDeadColor(whiteColor);
    setting.neighbor = false;
    neighborcount->Check(setting.neighbor);
    
}
void MainWindow::NeighborCheck(wxCommandEvent& event)
{
    setting.neighbor = !setting.neighbor;
    neighborcount->Check(setting.neighbor);
    drawing->Refresh();
}
void MainWindow::OnRandomize(wxCommandEvent& event)
{
    int seed = time(NULL);
    RandomizeGrid(seed);
}
void MainWindow::OnRandomizeWithSeed(wxCommandEvent& event)
{
    int seed = wxGetNumberFromUser("Enter Seed", "Seed: ", "Randomize with seed", 0, 0, LONG_MAX, this);
    RandomizeGrid(seed);
}
void MainWindow::RandomizeGrid(int seed)
{
    srand(seed);

    for (size_t i = 0; i < setting.gridSize; ++i)
    {
        for (size_t j = 0; j < setting.gridSize; ++j)
        {
            if (rand() % 2 == 0)
            {
                gameBoard[i][j] = true;
            }
            else
            {
                gameBoard[i][j] = false;
            }
        }
    }
    Refresh();
}
void MainWindow::SaveGameButton(wxCommandEvent& event)
{
    //Make it default to downloads
    wxFileDialog fileDialog(this, "Save Game of Life file", "", "", "Game of life files(*. cells) | *.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
   
    std::ofstream file("Game of life files(*. cells) | *.cells");
    if (file.is_open())
    {
        file.write((char*)this, sizeof(gameBoard.size()));
    }
    file.close();
}

void MainWindow::OpenFileButton(wxCommandEvent& event)
{
    wxFileDialog open(this, _("Open file"), wxEmptyString, wxEmptyString, "Files (*.cells) | *.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (open.ShowModal() == wxID_CANCEL)
    {
        return;
    }


    std::string buffer;
    std::ifstream file;
    int index = 0;

    file.open((std::string)open.GetPath());
    if (!file.is_open())
    {
        wxMessageBox("nope", "error");
        return;   
    }

    gameBoard.clear();
    std::vector<std::vector<bool>> temp;

    while (std::getline(file,buffer))
    {
        if (buffer.empty()) 
        {
            break;
        }
        
        temp.push_back(std::vector<bool>(buffer.size(), false));
        
        for (int i = 0; i < buffer.size(); i++)
        {
            if (buffer[i] == '*')
            {
                temp[index][i] = true;
            }
           
        }
        index++;
    }
    file.close();
   
    gameBoard = std::move(temp);
    UpdateStatusBar(livCells);
    drawing->Refresh();

    event.Skip();
}

void MainWindow::ExitButton(wxCommandEvent& event)
{
    Close(true);
}

void MainWindow::SaveAsButton(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, "Save Game of Life file", "", "", "Game of life files(*.cells) | *.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (fileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    std::ofstream fileStream;
    //GetFile name returns a wxString. So we cast the file name as a string
    fileStream.open((std::string)fileDialog.GetPath());
    if (fileStream.is_open())
    {
        for (size_t i = 0; i < gameBoard.size(); i++)
        {
            for (size_t j = 0; j < gameBoard[i].size(); j++)
            {
                if (gameBoard[i][j])
                {
                    fileStream << '*';
                }
                else
                {
                    fileStream << '.';
                }
            }
            fileStream << "\n";
        }

        fileStream.close();
    }
    event.Skip();
}

int MainWindow::NeighborCounter(int row, int col)
{
    //Int varaible used to repersent the living cell count
    int Livecount = 0;
    

    // A nexted for loop that covers a 3x3 grid  and checks if either is 0 if so wwe continue as we only want to count the neighbors
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            
            // This calulates the coordinates of the cells 
            int mRow = row + i;
            int mCol = col + j;

            //Checking if cell is out of range of the grid
            if (mRow >= 0 && mRow < setting.gridSize && mCol >= 0 && mCol < setting.gridSize)
            {
                //if game board is == to true add to the live count 
                if (gameBoard[mRow][mCol])
                {
                    Livecount++;
                }
            }
        }
    }
    
    //return the live count
    return Livecount;
}
void MainWindow::NextGen()
{
    GridInitializtion();
 
    livCells = 0;

    // A nested for loop counting till the size of the grid (15)
    for (int row = 0; row < setting.gridSize; ++row)
    {
        for (int col = 0; col < setting.gridSize; ++col)
        {
            // Calling NeighborCounter and passing in our iterators to determine how many of the cells neighbors are alive and storing it in a varaible called neighbors
            GridInitializtion();
            int neighbors = NeighborCounter(row, col);
            
            //Game of life rules 
            if (gameBoard[row][col] == true)
            {
                // if neighbor count is less than 2 and greater than 3 sandBox is set to false
                if (neighbors < 2 || neighbors > 3)
                {
                    gameBoard[row][col] = false;

                }
                else // else set the sandbox = to true and add to the living cell count
                {
                    gameBoard[row][col] = true;
                    ++livCells;

                }
                   
            }// else if neighbors is 3 set snadbox to true and add to the living cell count
            else if (neighbors == 3)
            {
                gameBoard[row][col] = true;
                ++livCells;
            }
            else// else set sandbox to false 
            {
                gameBoard[row][col] = false;
            }
        }
    }
    

    //Adding to the genration after all the checks are done 
    Gen += 1;

    //Updating the status bar
    UpdateStatusBar(livCells);

    //Refreshing the onpaint method
    Refresh();
   
}

void MainWindow::Timer(wxTimerEvent& event)
{
    // Calling the next gen method
    NextGen();

    // Passing in my time varaible
    setting.time;
}

void MainWindow::addToolFields(int ID, std::string name, wxBitmapBundle icon)
{
    toolBar->AddTool(ID, name, icon);
}



