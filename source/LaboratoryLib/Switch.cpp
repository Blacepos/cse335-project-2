/**
 * @file Switch.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Switch.h"

/// The image to use for the switch on
const std::wstring SwitchOnImage = L"/knifeswitch-on.png";

/// The image to use for the switch on
const std::wstring SwitchOffImage = L"/knifeswitch-off.png";

/// X location for connections for the left side of the switch
const int SwitchLeftX = -22;

/// X location for connections for the right side of the switch
const int SwitchRightX = 22;

/// Y location for sink
const int SwitchSinkY = -63;

/// Y position for the switch down source
const int SwitchSource0Y = -37;

/// Y position for the switch up source
const int SwitchSource1Y = -89;

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 * @param capacity The capacity of the connectors
 * @param rightSide Where to place the connectors (false corresponds to left)
 */
Switch::Switch(std::wstring imagesDir, std::wstring name, int capacity, bool rightSide)
    : PolyComponent(name), mRight(rightSide), mSink(imagesDir, capacity), mSource1(imagesDir, capacity), mSource2(imagesDir, capacity)
{
    SetImage(imagesDir + SwitchOffImage);
    BottomCenteredRectangle();

    mOnImage.SetImage(imagesDir + SwitchOnImage);
    mOnImage.BottomCenteredRectangle();

    mSink.SetPowerSinkUser(this);

    if (mRight)
    {
        mSink.SetPosition(SwitchRightX, SwitchSinkY);
        mSource1.SetPosition(SwitchRightX, SwitchSource0Y);
        mSource2.SetPosition(SwitchRightX, SwitchSource1Y);

        mSink.SetRotation(0.75);
        mSource1.SetRotation(0.75);
        mSource2.SetRotation(0.75);
    }
    else
    {
        mSink.SetPosition(SwitchLeftX, SwitchSinkY);
        mSource1.SetPosition(SwitchLeftX, SwitchSource0Y);
        mSource2.SetPosition(SwitchLeftX, SwitchSource1Y);

        mSink.SetRotation(0.25);
        mSource1.SetRotation(0.25);
        mSource2.SetRotation(0.25);
    }
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Switch::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    if (mOn)
    {
        mOnImage.DrawPolygon(graphics, GetX() + position.x, GetY() + position.y);
    }
    else
    {
        GetPolygon()->DrawPolygon(graphics, GetX() + position.x, GetY() + position.y);
    }

    mSink.Draw(graphics, position);
    mSource1.Draw(graphics, position);
    mSource2.Draw(graphics, position);
}

/**
 * Handle an event triggered by the animation
 * @param node An xml node
 */
void Switch::XmlEvent(wxXmlNode* node)
{
    mOn = node->GetAttribute(L"on", L"false") == L"true";
}

/**
 * Send power to both sources
 *
 * Sends 0 volts to one of the sources depending on the state of the switch
 * @param voltage How much power to send
 * @return The current in response
 */
double Switch::Power(double voltage)
{
    if (mOn)
    {
        return mSource2.Power(voltage) + mSource1.Power(0);
    }
    return mSource2.Power(0) + mSource1.Power(voltage);
}

/**
 * Reset this switch
 */
void Switch::Reset()
{
    mOn = false;
}

/**
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void Switch::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mSink.SetPosition(mSink.GetPosition() + GetPosition());
    mSource1.SetPosition(mSource1.GetPosition() + GetPosition());
    mSource2.SetPosition(mSource2.GetPosition() + GetPosition());
}
