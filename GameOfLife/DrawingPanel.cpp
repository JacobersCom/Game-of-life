#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

// Definition of the DrawingPanel constructor
DrawingPanel::DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard) : drawingBoard(gameBoard), wxPanel(parent) { // Initialize the base wxPanel class with the parent window and an ID
   
    // Set the background style to paint to control rendering
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind the paint event to the OnPaint method
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);

    // Bind the left up event to the onCLick method
    this->Bind(wxEVT_LEFT_UP, &DrawingPanel::onClick, this); 
}

// Definition of the DrawingPanel destructor
DrawingPanel::~DrawingPanel() {
    // Empty destructor
}



void DrawingPanel::Cell()
{
    // Grabing the Window size to access the Get width and heigh methods
    wxSize panel = this->GetClientSize();

    // Taking get width and dividing it by the grid size (15)
    cellWidth = (panel.GetWidth() / gridSize);

    // Taking get height and dividing it by the grid size (15)
    cellHeight = (panel.GetHeight() / gridSize);
}

// Definition of the OnPaint method, which handles paint events
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
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
    context->SetPen(*wxBLACK_PEN);

    // Set the brush color to white for filling shapes
    context->SetBrush(*wxWHITE_BRUSH); 
    
    // loop over the girdSize and adding rows to it
    for (int row = 0; row < gridSize; ++row) 
    {
        // looping over the girdSize and adding columes to it
        for (int col = 0; col < gridSize; ++col)
        {
            // x is col times cellwidth
            int x = row * cellWidth;

            // y is row times cell height
            int y = col * cellHeight;

                if (drawingBoard[row][col])
                {
                    context->SetBrush(*wxRED);
                }
                else
                {
                    context->SetBrush(*wxWHITE);
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
}

void DrawingPanel::SetGridSize(int newGrid)
{
    gridSize = newGrid;
    Cell();
    this->Refresh();
}

void DrawingPanel::onClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();

   
    int rowClicked = x / cellWidth;
    int colClicked = y / cellHeight;
    
    if (rowClicked >= 0 && rowClicked < gridSize && colClicked >= 0 && colClicked < gridSize)
    {
        drawingBoard[rowClicked][colClicked] = !drawingBoard[rowClicked][colClicked];
       
         Refresh();
    }

}

