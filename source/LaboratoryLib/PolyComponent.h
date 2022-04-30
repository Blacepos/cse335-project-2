/**
 * @file PolyComponent.h
 * @author Joshua Austin
 *
 * Component which has a polygon and a position
 */

#ifndef CANADIANEXPERIENCE_POLYCOMPONENT_H
#define CANADIANEXPERIENCE_POLYCOMPONENT_H

#include "Component.h"
#include "Polygon.h"

/**
 * Component which has a polygon and a position
 */
class PolyComponent : public Component {
private:
    /// The drawable used by this component
    cse335::Polygon mPolygon;

    /// The position of this drawable component
    wxPoint mPosition = wxPoint(0, 0);

protected:
    explicit PolyComponent(std::wstring name);

public:
    /// Default constructor/disabled
    PolyComponent() = delete;

    /// Copy constructor/disabled
    PolyComponent(const PolyComponent&) = delete;

    /// Assignment operator/disabled
    void operator=(const PolyComponent&) = delete;

    /**
     * Get the polygon for this component
     * @return A pointer to the polygon object
     */
    cse335::Polygon* GetPolygon() { return &mPolygon; }

    /**
     * Set the position of this component
     * @param x The new x position
     * @param y The new y position
     */
    virtual void SetPosition(int x, int y) { mPosition.x = x, mPosition.y = y; }

    /**
     * Get the position of this component
     * @return The position as a point
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Get the x coordinate of this component
     * @return The x coordinate
     */
    int GetX() const { return mPosition.x; }

    /**
     * Get the y coordinate of this component
     * @return The y coordinate
     */
    int GetY() const { return mPosition.y; }

    /**
    * Set this image for this shape
    * @param image The image filename
    */
    void SetImage(std::wstring image) { mPolygon.SetImage(image); }

    /**
     * Create a rectangle.
     *
     * If the height parameter is not supplied and an image
     * has been set, the height will be computed so as to
     * keep the original image aspect ratio correct.
     *
     * @param x Left side X
     * @param y Bottom left Y
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     */
    void Rectangle(int x, int y, int width=0, int height=0) { mPolygon.Rectangle(x, y, width, height); }

    /**
     * Create a rectangle where 0,0 is the bottom center of the rectangle.
     *
     * Must set an image first
     */
    void BottomCenteredRectangle() { mPolygon.BottomCenteredRectangle(); }
};

#endif //CANADIANEXPERIENCE_POLYCOMPONENT_H
