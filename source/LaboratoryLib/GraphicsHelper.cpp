/**
 * @file GraphicsHelper.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "GraphicsHelper.h"

using namespace cse335;

/**
 * Convenience function to draw a crosshair.
 * @param graphics Graphics object to draw on
 * @param x X location for crosshair center
 * @param y Y location for crosshair center
 * @param size Size (width and height) of the crosshair in pixels (optional, default=
 * @param color Crosshair color (optional, default=red)
 */
void GraphicsHelper::DrawCrosshair(std::shared_ptr<wxGraphicsContext> graphics, int x, int y,
        int size, wxColor color)
{
    wxPen pen(color);
    graphics->SetPen(pen);
    graphics->StrokeLine(x-size/2, y, x+size/2, y);
    graphics->StrokeLine(x, y-size/2, x, y+size/2);
}

/**
 * Convert a rotation and length into a 2D vector.
 * @param angle Angle in rotations (0-1 for a revolution)
 * @param length Length.
 * @return
 */
wxPoint2DDouble GraphicsHelper::ToVector(double angle, double length)
{
    double sn = sin(angle * M_PI * 2);
    double cs = cos(angle * M_PI * 2);
    return {sn * length, -cs * length};
}

/**
 * Convert a rotation and length into a 2D vector.
 * @param angle Angle in rotations (0-1 for a revolution)
 * @param length Length.
 * @return
 */
wxPoint GraphicsHelper::ToIntVector(double angle, double length)
{
    double sn = sin(angle * M_PI * 2);
    double cs = cos(angle * M_PI * 2);
    return {(int)(sn * length), -(int)(cs * length)};
}