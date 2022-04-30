/**
 * @file EquipmentRack.h
 * @author Joshua Austin
 *
 * Component which handles positioning other components
 */

#ifndef CANADIANEXPERIENCE_EQUIPMENTRACK_H
#define CANADIANEXPERIENCE_EQUIPMENTRACK_H

#include "PolyComponent.h"
#include "Polygon.h"

class Shape;

/**
 * Component which handles positioning other components
 */
class EquipmentRack : public PolyComponent {
private:
    /// A place to store all of the blank panel shapes
    std::vector<std::shared_ptr<Shape>> mBlankPanels;

    int FromRackUnits(int ru) const;

public:
    EquipmentRack(std::wstring imagesDir, std::wstring name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    void AddBlankPanel(std::wstring filename, int position);

    void SetPanelPosition(std::shared_ptr<PolyComponent> equipment, int y, int x=0);
};

#endif //CANADIANEXPERIENCE_EQUIPMENTRACK_H
