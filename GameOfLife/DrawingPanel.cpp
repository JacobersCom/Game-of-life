#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

// Definition of the DrawingPanel constructor
DrawingPanel::DrawingPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) { // Initialize the base wxPanel class with the parent window and an ID
    this->SetBackgroundStyle(wxBG_STYLE_PAINT); // Set the background style to paint to control rendering
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this); // Bind the paint event to the OnPaint method
}

// Definition of the DrawingPanel destructor
DrawingPanel::~DrawingPanel() {
    // Empty destructor
}

// Definition of the OnPaint method, which handles paint events
void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this); // Create a buffered device context to reduce flicker
    dc.Clear(); // Clear the drawing area

    wxGraphicsContext* context = wxGraphicsContext::Create(dc); // Create a graphics context for drawing
    if (!context) { // Check if the graphics context creation failed
        return; // Exit the method if the context is null
    }

    context->SetPen(*wxBLACK_PEN); // Set the pen color to black for drawing outlines
    context->SetBrush(*wxWHITE_BRUSH); // Set the brush color to white for filling shapes
    
    wxSize panel = GetClientSize(); // Grabing the Window size to access the Get width and heigh methods
    
    int cellWidth = panel.GetWidth() / gridSize; // Taking get width and dividing it by the grid size (15)
    int cellHeight = panel.GetHeight() / gridSize; // Taking get height and dividing it by the grid size (15)

    for (int row = 0; row < gridSize; ++row) // loop over the girdSize and adding rows to it
    {
        for (int col = 0; col < gridSize; ++col)// looping over the girdSize and adding columes to it
        {
            int x = col * cellWidth; // x is col times cellwidth
            int y = row * cellHeight;// y is row times cell height
            context->DrawRectangle(x, y, cellWidth, cellHeight); // Taking the context variable and calling DrawRec and passing in the x,y and width and height
            
        }
    }
    delete context; // Clean up and delete the graphics context
}

void DrawingPanel::setSize(wxSize& size)
{
    wxPanelBase base; // wxPanelbase object
    base.SetSize(size); // Calling set size on the base and passing in the size reference paramenter
    Refresh(); // It erases the orginal back ground and prints another during resizing the window
}

