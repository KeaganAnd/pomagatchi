#include <stdbool.h>
#include "raylib.h"  
#include "buttons.h"


// Checks if the mouse is over an ellipse button given top-left position, size, and uiScale
bool IsMouseOverEllipse(Vector2 mouse, Vector2 topLeft, Vector2 size, float uiScale)
{
    // Compute scaled ellipse radius
    float radiusX = (size.x * uiScale) * 0.5f;
    float radiusY = (size.y * uiScale) * 0.5f;

    // Compute center of the ellipse
    Vector2 center = {
        topLeft.x + radiusX,
        topLeft.y + radiusY
    };

    // Check if mouse is inside ellipse
    float dx = mouse.x - center.x;
    float dy = mouse.y - center.y;
    return ((dx*dx)/(radiusX*radiusX) + (dy*dy)/(radiusY*radiusY)) <= 1.0f;
}
