#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::onClick)
wxEND_EVENT_TABLE()


// Definition of the DrawingPanel constructor
DrawingPanel::DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard, gameSetting* settings) : window(static_cast<MainWindow*>(parent)), drawingBoard(gameBoard), wxPanel(parent), settings(settings) { // Initialize the base wxPanel class with the parent window and an ID
   
    // Set the background style to paint to control rendering

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    int gridSize = settings->GetGridSize();

}

// Definition of the DrawingPanel destructor
DrawingPanel::~DrawingPanel() {
    // Empty destructor
}



void DrawingPanel::Cell()
{
    int gridSize = settings->GetGridSize();
    // Grabing the Window size to access the Get width and heigh methods
    wxSize panel = this->GetClientSize();
    if (gridSize == NULL)
    {
        
    }
    else
    {

        cellWidth = (panel.GetWidth() / gridSize);

        // Taking get height and dividing it by the grid size (15)
        cellHeight = (panel.GetHeight() / gridSize);
    }
        // Taking get width and dividing it by the grid size (15)

}

// Definition of the OnPaint method, which handles paint events
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
   

    int gridSize = settings->GetGridSize();
    // Create a buffered device context to reduce flicker
    wxAutoBufferedPaintDC dc(this);
   
    // Clear the drawing area
    dc.Clear(); 


    // Create a graphics context for drawing
    wxGraphicsContext* context = wxGraphicsContext::Create(dc); 
    
    // Check if the graphics context creation failed
    if (!context) { 
        // Exit the method if the context is null
        return; 
    }

    // Set the pen color to black for drawing outlines
    context->SetPen(*wxBLACK);

    // Set the brush color to white for filling shapes
    context->SetBrush(*wxWHITE); 
    
    // loop over the girdSize and adding rows to it
    for (int row = 0; row < gridSize; ++row) 
    {
        // looping over the girdSize and adding columes to it
        for (int col = 0; col < gridSize; ++col)
        {
            int neighbors = window->NeighborCounter(row, col);
            if (neighbors > 0 && settings->neighbor)
            {
                context->SetFont(wxFontInfo(16), *wxRED);
                wxString neighborCount = wxString::Format("%d", neighbors);
                double width, heigh;
                context->GetTextExtent(neighborCount, &width, &heigh);
                int x = row * cellWidth + (cellWidth - width) /2;
                int y = col * cellHeight + (cellHeight - heigh) /2;
                context->DrawText(neighborCount, x, y);
                this->Refresh();
            }
            
            // x is col times cellwidth
            int x = row * cellWidth;

            // y is row times cell height
            int y = col * cellHeight;

                if (drawingBoard[row][col])
                {
                    context->SetBrush(settings->GetColor());
                }
                else
                {
                    context->SetBrush(settings->GetDeadColor());
                }

            // Taking the context variable and calling DrawRec and passing in the x,y and width and height
            context->DrawRectangle(x, y, cellWidth, cellHeight); 
            
        }
    }
    // Clean up and delete the graphics context
   
    delete context; 
    
}

void DrawingPanel::setSize(wxSize& size)
{
    // Calling set size on the base and passing in the size reference paramenter
    wxPanel::SetSize(size); 

    Cell();

    // It erases the orginal back ground and prints another during resizing the window
    this->Refresh(); 
    settings->SaveData();
}

void DrawingPanel::SetGridSize(int newGrid)
{
    int gridSize = settings->GetGridSize();
    // Calulates the cell width and height and refreshes the current obj
    gridSize = newGrid;
    Cell();
    this->Refresh();
    settings->SaveData();
}

void DrawingPanel::onClick(wxMouseEvent& event)
{ 
    int gridSize = settings->GetGridSize();
    //Getting the point of where the mouse clicked
    int x = event.GetX();
    int y = event.GetY();

   // Using where the mouse clicked to calulate the row and col 
    int rowClicked = x / cellWidth;
    int colClicked = y / cellHeight;

    // checking if where the mouse clicked was within range of the grid
    if (rowClicked >= 0 && rowClicked < gridSize && colClicked >= 0 && colClicked < gridSize)
    {
        // if drawingBoard is true set it to false and take from the living count
        if (drawingBoard[rowClicked][colClicked])
        {
            drawingBoard[rowClicked][colClicked] = false;
            window->UpdateStatusBar(-1);
        }
        else
        {
            //else set it to true and add to the count
            drawingBoard[rowClicked][colClicked] = true;
            window->UpdateStatusBar(1);

        }
        //refresh the onPaint method
        
        Refresh();
    }
  




}

