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
void DrawingPanel::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this); // Create a buffered device context to reduce flicker
    dc.Clear(); // Clear the drawing area

    wxGraphicsContext* context = wxGraphicsContext::Create(dc); // Create a graphics context for drawing
    if (!context) { // Check if the graphics context creation failed
        return; // Exit the method if the context is null
    }

    context->SetPen(*wxBLUE); // Set the pen color to black for drawing outlines
    context->SetBrush(*wxYELLOW); // Set the brush color to white for filling shapes

    context->DrawRectangle(10, 10, 100, 100); // Draw a rectangle with the specified position and size

    delete context; // Clean up and delete the graphics context
}