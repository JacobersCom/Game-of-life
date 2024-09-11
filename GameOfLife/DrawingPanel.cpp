#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

// Definition of the DrawingPanel constructor
DrawingPanel::DrawingPanel(MainWindow* parent, std::vector<std::vector<bool>>& gameBoard) : drawingBoard(gameBoard), wxPanel(parent, wxID_ANY) { // Initialize the base wxPanel class with the parent window and an ID
   
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
    
    // Grabing the Window size to access the Get width and heigh methods
    wxSize panel = GetClientSize(); 
    
    // Taking get width and dividing it by the grid size (15)
    int cellWidth = panel.GetWidth() / gridSize; 

    // Taking get height and dividing it by the grid size (15)
    int cellHeight = panel.GetHeight() / gridSize; 

   
    

    // loop over the girdSize and adding rows to it
    for (int row = 0; row < gridSize; ++row) 
    {
        // looping over the girdSize and adding columes to it
        for (int col = 0; col < gridSize; ++col)
        {
            if (drawingBoard[row][col] == true)
            {
                
            }
            // x is col times cellwidth
            int x = col * cellWidth;

            // y is row times cell height
            int y = row * cellHeight;

            // Taking the context variable and calling DrawRec and passing in the x,y and width and height
            context->DrawRectangle(x, y, cellWidth, cellHeight); 
            
        }
    }
    // Clean up and delete the graphics context
    delete context; 
}

void DrawingPanel::setSize(wxSize& size)
{
    // wxPanelbase object
    wxPanelBase base; 

    // Calling set size on the base and passing in the size reference paramenter
    base.SetSize(size); 

    // It erases the orginal back ground and prints another during resizing the window
    Refresh(); 
}

void DrawingPanel::SetGridSize(int newGrid)
{
    gridSize = newGrid;
}

void DrawingPanel::onClick(wxMouseEvent& event)
{
    int x = event.GetX();
    int y = event.GetY();

    wxSize panel = GetClientSize(); // Grabing the Window size to access the Get width and heigh methods

    int cellWidth = panel.GetWidth() / gridSize; // Taking get width and dividing it by the grid size (15)
    int cellHeight = panel.GetHeight() / gridSize; // Taking get height and dividing it by the grid size (15)

    int rowClicked = x / cellWidth;
    int colClicked = y / cellHeight;
    drawingBoard[rowClicked][colClicked];
    Refresh();

}

