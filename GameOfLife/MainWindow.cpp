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
wxEND_EVENT_TABLE()

// Definition of the MainWindow constructor
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(800, 600)), Gen(0), livCells(0), time(175) { // Initialize the base wxFrame class with position and size
   
    // Creating my status bar
    statusBar = CreateStatusBar();
    
    // Calling the method for my bar text
    StatusBarText();
    
    // Creating my tool bar
    toolBar = CreateToolBar();

    //Initialzing the wxTimer pointer
    timer = new wxTimer(this, 10004);

    //Bitmap for the playerIcon that takes the C style char array
    wxBitmap playicon(play_xpm);
    //A helper method that takes a int string and wxBitmap and adds the Play button to the tool bar
    addToolFields(10000, "Play", playicon);
    wxBitmap pauseicon(pause_xpm);
    addToolFields(10001, "Pause", pauseicon);;
    wxBitmap trashicon(trash_xpm);
    addToolFields(10002, "Trash", trashicon);
    wxBitmap nexticon(next_xpm);
    addToolFields(10003, "Next", nexticon);

    //Used to finalizes the placement of the tool bar 
    toolBar->Realize();

    // Initialize the DrawingPanel with "this" as the parent
    drawing = new DrawingPanel(this, gameBoard); 
    
    GridInitializtion();

    this->Layout();
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

// Initializing the grid 
void MainWindow::GridInitializtion()
{
    // Getting the ClientSize
    wxSize size = this->GetClientSize();
    
    // Making the vector the same size as the grid(15)
    gameBoard.resize(gridSize);

    //resizing the vectors inside the vector
    for (size_t i = 0; i < gameBoard.size(); i++)
    {
        gameBoard[i].resize(gridSize);
    }

    //Calling the set grid size from drawing panel and passing in the gridsize 
    drawing->SetGridSize(gridSize);
}

//Setting the status bar
void MainWindow::StatusBarText()
{

    std::string bar = "   \t\t\t\t\t\t\t\t\t\t\t\t\tGeneration: " + std::to_string(Gen) + "\t\t\t\t|\t\t\t\t" + std::to_string(livCells) + " :Living";
    statusBar->SetStatusText(bar);
}

//When play is clicked a timer will start. Time is = to 50
void MainWindow::PlayButton(wxCommandEvent& event)
{
    //timer is pointer of wxtime pointer to the start method to start a timer for 50 milisecs
    timer->Start(time);
}

// Clearing the screen
void MainWindow::TrashButton(wxCommandEvent& event)
{
    // Nested for loop resetting the vector of vectors to false
    for (int i = 0; i < gameBoard.size(); i++)
    {
        for (int j = 0; j < gameBoard.size(); j++)
        {
            gameBoard[i][j] = false;
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

//Pausing the play method
void MainWindow::PauseButton(wxCommandEvent& event)
{
    //Stops timer in play method
    timer->Stop();
}

//Class NextGen method to move to the next gen
void MainWindow::NextButton(wxCommandEvent& event)
{
    NextGen();
}

// counting the number of living cells around a cell
int MainWindow::NeighborCounter(int row, int col)
{
    //Int varaible used to repersent the living cell count
    int Livecount = 0;

    // A nexted for loop that covers a 3x3 grid  and checks if either is 0 if so wwe continue as we only want to count the neighbors
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            
            // This calulates the coordinates of the cells 
            int mRow = row + i;
            int mCol = col + j;

            //Checking if cell is out of range of the grid
            if (mRow >= 0 && mRow < gridSize && mCol >= 0 && mCol < gridSize)
            {
                //if game board is == to true add to the live count 
                if (gameBoard[mRow][mCol] == true)
                {
                    Livecount += 1;
                }
            }
        }
    }
    
    //return the live count
    return Livecount;
}

// Handles advancing the game of life generation
void MainWindow::NextGen()
{
    //varaible vector 
    std::vector<std::vector<bool>> sandbox;

    // resizing the vector and the vector's vectors to the grid size
    sandbox.resize(gridSize);
    for (int i = 0; i < sandbox.size(); i++)
    {
        sandbox[i].resize(gridSize);
    }
    
    //Setting Living cells to 0
    livCells = 0;

    // A nested for loop counting till the size of the grid (15)
    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            // Calling NeighborCounter and passing in our iterators to determine how many of the cells neighbors are alive and storing it in a varaible called neighbors
            int neighbors = NeighborCounter(row, col);
            
            //Game of life rules 
            if (gameBoard[row][col] == true)
            {
                // if neighbor count is less than 2 and greater than 3 sandBox is set to false
                if (neighbors < 2 || neighbors > 3)
                {
                    sandbox[row][col] = false;

                }
                else // else set the sandbox = to true and add to the living cell count
                {
                    sandbox[row][col] = true;
                    ++livCells;

                }
                   
            }// else if neighbors is 3 set snadbox to true and add to the living cell count
            else if (neighbors == 3)
            {
                sandbox[row][col] = true;
                ++livCells;
            }
            else// else set sandbox to false 
            {
                sandbox[row][col] = false;
            }
        }
    }
    
    //Overwriting the data of gameBoard with sandBox and discarding sandBox
    gameBoard.swap(sandbox);

    //Adding to the genration after all the checks are done 
    Gen += 1;

    //Updating the status bar
    UpdateStatusBar(livCells);

    //Refreshing the onpaint method
    Refresh();
   
}

// Time method setting a timer
void MainWindow::Timer(wxTimerEvent& event)
{
    // Calling the next gen method
    NextGen();

    // Passing in my time varaible
    time;
}

//Helper method for adding the right arugments to the Addtool method
void MainWindow::addToolFields(int ID, std::string name, wxBitmap icon)
{
    toolBar->AddTool(ID, name, icon);
}

//Updating my status bar
void MainWindow::UpdateStatusBar(int alive)
{  
    //Adding the alive cells to livcells
    livCells += alive;
   
    // updating the test for the bar
    StatusBarText();
}



