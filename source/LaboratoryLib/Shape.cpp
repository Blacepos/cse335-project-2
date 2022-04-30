/**
 * @file Shape.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Shape.h"

/**
 * Constructor
 * @param name The name of this shape
 */
Shape::Shape(std::wstring name)
        : PolyComponent(name)
{
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->DrawPolygon(graphics, position.x + GetX(), position.y + GetY());
}
