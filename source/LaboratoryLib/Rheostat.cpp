/**
 * @file Rheostat.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Rheostat.h"

/// The rheostat image
const std::wstring RheostatImage = L"/rheostat.png";

/// The rheostat knob image
const std::wstring RheostatKnobImage = L"/rheostat-knob.png";

/// X location for sink
const int RheostatSinkX = -40;

/// X location for source
const int RheostatSourceX = 40;

/// Y location for sink
const int RheostatSinkY = -40;

/// Y position for source
const int RheostatSourceY = -40;

/// The width of the rheostat
const int RheostatWidth = 80;

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 * @param capacity The capacity of the connectors
 */
Rheostat::Rheostat(std::wstring imagesDir, std::wstring name, int capacity)
        : PolyComponent(name), mSink(imagesDir, capacity), mSource(imagesDir, capacity)
{
    SetImage(imagesDir + RheostatImage);
    Rectangle(-RheostatWidth/2, 0, RheostatWidth);

    mKnob.SetImage(imagesDir + RheostatKnobImage);
    mKnob.CenteredSquare(RheostatWidth);

    mSink.SetPowerSinkUser(this);

    mSink.SetPosition(RheostatSinkX, RheostatSinkY);
    mSink.SetRotation(0.25);

    mSource.SetPosition(RheostatSourceX, RheostatSourceY);
    mSource.SetRotation(0.75);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Rheostat::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->DrawPolygon(graphics, GetX() + position.x, GetY() + position.y);

    mKnob.SetRotation(mRotation);
    mKnob.DrawPolygon(graphics, GetX() + position.x, GetY() + position.y - RheostatWidth/2);

    mSink.Draw(graphics, position);
    mSource.Draw(graphics, position);
}

/**
 * Handle an event triggered by the animation
 * @param node An xml node
 */
void Rheostat::XmlEvent(wxXmlNode* node)
{
    double destination;
    node->GetAttribute(L"rotate-to", L"0").ToDouble(&destination);
    double duration;
    node->GetAttribute(L"duration", L"0").ToDouble(&duration);
    RotateTo(destination, duration);
}

/**
 * Send power to both sources
 *
 * Sends 0 volts to one of the sources depending on the state of the switch
 * @param voltage How much power to send
 * @return The current in response
 */
double Rheostat::Power(double voltage)
{
    return mSource.Power(voltage * mRotation * 2);
}

/**
 * Reset this rheostat
 */
void Rheostat::Reset()
{
    mRotation = 0.0;
    mRotationsPerSecond = 0.0;
    mDestination = 0.0;
}

/**
 * Tell the rheostat to start rotating to a destination angle
 * @param angle What angle to stop at
 * @param seconds How long it should take to reach the angle
 */
void Rheostat::RotateTo(double angle, double seconds)
{
    // clamp the angle below 0.5 and above 0
    angle = angle > 0.5 ? 0.5 : angle;
    angle = angle < 0.0 ? 0.0 : angle;

    mRotationsPerSecond = (angle - mRotation) / seconds;
    mDestination = angle;
}

/**
 * Set the current time
 *
 * Updates the rotation of the wheel and upcalls to Component
 * @param time The new time
 */
void Rheostat::SetTime(double time)
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
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void Rheostat::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mSink.SetPosition(mSink.GetPosition() + GetPosition());
    mSource.SetPosition(mSource.GetPosition() + GetPosition());
}
