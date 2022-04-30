/**
 * @file ZPM.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "ZPM.h"
#include <sstream>


/// The image to use for the ZPM
const std::wstring ZpmImage = L"/zpm.png";

/// The ZPM output voltage
const double ZPMVoltage = 1000;

/// X offset relative to the bottom center of the
/// ZPM image to where the statistics are displayed
const int StatsOffsetX = -22;

/// Y offset to where to draw the voltage in pixels
const int VoltageOffsetY = -70;

/// Y offset to where to darw the current in pixels
const int CurrentOffsetY = -50;

/// Location of the source on the ZPM
const wxPoint ZPMSourcePosition = wxPoint(20, -15);

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 */
ZPM::ZPM(std::wstring imagesDir, std::wstring name)
        : PolyComponent(name), mSource(imagesDir, 1000.0)
{
    SetImage(imagesDir + ZpmImage);
    GetPolygon()->BottomCenteredRectangle();

    mSource.SetPosition(ZPMSourcePosition.x, ZPMSourcePosition.y);
    mSource.SetRotation(0.75);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void ZPM::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    auto polygon = GetPolygon();
    auto pos = GetPosition();
    polygon->DrawPolygon(graphics, position.x + pos.x, position.y + pos.y);

    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxWHITE);

    // Convert voltage and current to string
    std::wstringstream str;
    str << ZPMVoltage;
    std::wstring wstr = str.str();
    graphics->DrawText(wstr, StatsOffsetX + position.x + pos.x,
                                 VoltageOffsetY + position.y + pos.y);

    std::wstringstream str2;
    str2 << static_cast<int>(mCurrent);
    wstr = str2.str();
    graphics->DrawText(wstr, StatsOffsetX + position.x + pos.x,
                                 CurrentOffsetY + position.y + pos.y);

    mSource.Draw(graphics, position);
}

/**
 * Send power to the rest of the system
 */
void ZPM::SendPower()
{
    mCurrent = mSource.Power(ZPMVoltage);
}

/**
 * Reset the ZPM
 */
void ZPM::Reset()
{
    mCurrent = 0.0;
}

/**
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void ZPM::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mSource.SetPosition(mSource.GetPosition() + GetPosition());
}
