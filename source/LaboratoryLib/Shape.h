/**
 * @file Shape.h
 * @author Joshua Austin
 *
 * Basic component with a single drawable
 */

#ifndef CANADIANEXPERIENCE_SHAPE_H
#define CANADIANEXPERIENCE_SHAPE_H

#include "PolyComponent.h"
#include "Polygon.h"

/**
 * Basic component with a single drawable
 */
class Shape : public PolyComponent {
public:
    Shape(std::wstring name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;
};

#endif //CANADIANEXPERIENCE_SHAPE_H
