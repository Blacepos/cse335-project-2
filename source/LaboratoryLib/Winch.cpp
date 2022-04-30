/**
 * @file Winch.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Winch.h"

/// Image for the winch panel in the rack
const std::wstring WinchBackgroundImage = L"/winch-12u-back.png";

/// Image for the winch handle (wheel)
const std::wstring WinchWheelImage = L"/winch-12u-wheel.png";

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 */
Winch::Winch(std::wstring imagesDir, std::wstring name)
    : PolyComponent(name)
{
    SetImage(imagesDir + WinchWheelImage);
    GetPolygon()->CenteredSquare();

    mBackground.SetImage(imagesDir + WinchBackgroundImage);
    mBackground.BottomCenteredRectangle();
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Winch::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->SetRotation(mRotation);
    mBackground.DrawPolygon(graphics, GetX() + position.x, GetY() + position.y);
    GetPolygon()->DrawPolygon(graphics, GetX() + position.x, GetY() + position.y - mBackground.GetImageHeight()/2);
}

/**
 * Handle an event triggered by the animation
 * @param node An xml node
 */
void Winch::XmlEvent(wxXmlNode* node)
{
    double destination;
    node->GetAttribute(L"rotate-to", L"0").ToDouble(&destination);
    double duration;
    node->GetAttribute(L"duration", L"0").ToDouble(&duration);
    RotateTo(destination, duration);
    mMotionSource.Drive(destination, duration);
}

/**
 * Tell the winch to start rotating to a destination angle
 * @param angle What angle to stop at
 * @param seconds How long it should take to reach the angle
 */
void Winch::RotateTo(double angle, double seconds)
{
    mRotationsPerSecond = (angle - mRotation) / seconds;
    mDestination = angle;
}

/**
 * Set the current time
 *
 * Updates the rotation of the wheel and upcalls to Component
 * @param time The new time
 */
void Winch::SetTime(double time)
{
    // record the time before the update
    double elapsed = GetTime();
    PolyComponent::SetTime(time);

    // calculate the elapsed time after the update
    elapsed = GetTime() - elapsed;

    // if rotating in the positive direction and we've passed the goal or the opposite case
    if (mRotation >= mDestination && mRotationsPerSecond > 0 ||
        mRotation <= mDestination && mRotationsPerSecond < 0)
    {
        mRotationsPerSecond = 0.0;
    }

    mRotation += elapsed * mRotationsPerSecond;
}

/**
 * Reset the winch
 */
void Winch::Reset()
{
    mRotation = 0.0;
    mRotationsPerSecond = 0.0;
    mDestination = 0.0;

}
