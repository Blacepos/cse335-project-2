/**
 * @file EquipmentRack.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "EquipmentRack.h"
#include "Shape.h"


/// The rack image
const std::wstring RackImage = L"/rack.png";

/// Width of the rack panel in inches
const double RackPanelWidth = 19;

/// Height of a rack unit in inches
const double RackUnit = 1.75;

/// Total width to draw the rack
const int RackWidthPixels = 131;

/// Width of a rack panel in pixels
const int RackPanelWidthPixels = 113;

/// Pixels per inch in the rack image
const double RackPixelsPerInch = RackPanelWidthPixels / RackPanelWidth;

/// A single U size in pixels
const double RackUPixels = RackPixelsPerInch * RackUnit;

/// The number of pixels below the bottom of the first
/// rack slot (unit)
const double RackPixelsBelowFirstSlot = 15;

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 */
EquipmentRack::EquipmentRack(std::wstring imagesDir, std::wstring name)
        : PolyComponent(name)
{
    SetImage(imagesDir + RackImage);
    Rectangle(-RackWidthPixels/2, 0, RackWidthPixels);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void EquipmentRack::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->DrawPolygon(graphics, position.x + GetPosition().x, position.y + GetPosition().y);

    // Draw the blank panels
    for (auto const& panel : mBlankPanels)
    {
        panel->Draw(graphics, position);
    }
}

/**
 * Create a blank panel
 * @param filename The name of the image file of the panel
 * @param position The position in rack units
 */
void EquipmentRack::AddBlankPanel(std::wstring filename, int position)
{
    auto panel = std::make_shared<Shape>(L"");
    panel->SetImage(filename);
    panel->Rectangle(-RackPanelWidthPixels/2, 0);
    panel->SetPosition(GetX(), FromRackUnits(position));
    mBlankPanels.push_back(panel);
}

/**
 * Set the position of a component on this rack
 * @param equipment The component to set the position of
 * @param x The x position on the panel in pixels
 * @param y The y position on the panel in rack units
 */
void EquipmentRack::SetPanelPosition(std::shared_ptr<PolyComponent> equipment, int y, int x)
{
    equipment->SetPosition(GetX()+x, FromRackUnits(y));
}

/**
 * Calculate the position of on the rack given an amount in rack units
 * @param ru A height in rack units
 * @return The position in pixels
 */
int EquipmentRack::FromRackUnits(int ru) const
{
    return GetY() - lround(RackPixelsBelowFirstSlot + RackUPixels * ru);;
}