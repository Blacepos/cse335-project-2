/**
 * @file VoltageMeter.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "VoltageMeter.h"

/// The image to use for the voltage meter (113 x 52)
const std::wstring MeterImage = L"/meters-5u.png";

/// The x position of the sink
const int MeterSinkX = -56;

/// The x position of the source
const int MeterSourceX = 56;

/// The y position of both the sink and the source
const int MeterSinkSourceY = -26;

/// How far from the point of rotation the needle line starts
const double NeedleLengthStart = 14;

/// The far from the point of rotation the needle line ends
const double NeedleLengthEnd = 26;

/// The y position of the needles
const int NeedleY = -15;

/// The x position of the voltage needle
const int NeedleVoltageX = -24;

/// The x position of the current needle
const int NeedleCurrentX = 24;

/// The minimum rotation angle of a needle
const double NeedleMinRotation = 0.125;

/// The maximum rotation angle of a needle
const double NeedleMaxRotation = 0.375;

/// At how much voltage the voltage needle will be all the way to the right
const double NeedleVoltageMaxValue = 1000.0;

/// At how much current the current needle will be all the way to the right
const double NeedleCurrentMaxValue = 400.0;

/// The position of the voltage needle
const wxPoint NeedleVoltagePos = wxPoint(NeedleVoltageX, NeedleY);

/// The position of the current needle
const wxPoint NeedleCurrentPos = wxPoint(NeedleCurrentX, NeedleY);

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 * @param capacity The capacity of the connectors
 */
VoltageMeter::VoltageMeter(std::wstring imagesDir, std::wstring name, int capacity)
    :PolyComponent(name), mSink(imagesDir, capacity), mSource(imagesDir, capacity)
{
    SetImage(imagesDir + MeterImage);
    BottomCenteredRectangle();

    mSink.SetPowerSinkUser(this);
    mSink.SetPosition(MeterSinkX, MeterSinkSourceY);
    mSink.SetRotation(0.25);

    mSource.SetPosition(MeterSourceX, MeterSinkSourceY);
    mSource.SetRotation(0.75);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void VoltageMeter::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->DrawPolygon(graphics, GetX() + position.x, GetY() + position.y);

    auto voltageRotation = MapValueRange(mVoltage, 0, NeedleVoltageMaxValue, NeedleMinRotation, NeedleMaxRotation);
    auto currentRotation = MapValueRange(mCurrent, 0, NeedleCurrentMaxValue, NeedleMinRotation, NeedleMaxRotation);
    DrawNeedle(graphics, GetPosition() + position + NeedleVoltagePos, voltageRotation);
    DrawNeedle(graphics, GetPosition() + position + NeedleCurrentPos, currentRotation);

    mSink.Draw(graphics, position);
    mSource.Draw(graphics, position);
}

/**
 * Send power to each source
 * @param voltage How much power to send
 * @return The cumulative current in amps
 */
double VoltageMeter::Power(double voltage)
{
    mVoltage = voltage;
    mCurrent = mSource.Power(voltage);
    return mCurrent;
}

/**
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void VoltageMeter::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mSink.SetPosition(mSink.GetPosition() + GetPosition());
    mSource.SetPosition(mSource.GetPosition() + GetPosition());
}

/**
 * Draw a needle. A rotated black line with one end at a given position
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 * @param rotation The rotation of the needle in whole rotations, with 0 pointing in the -x direction
 */
void VoltageMeter::DrawNeedle(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position, double rotation)
{
    double radians = rotation * M_PI * 2;
    double cosRotation = -cos(radians);
    double sinRotation = -sin(radians);
    wxPoint start = wxPoint(NeedleLengthStart * cosRotation,
                            NeedleLengthStart * sinRotation) + position;
    wxPoint end = wxPoint(NeedleLengthEnd * cosRotation,
                          NeedleLengthEnd * sinRotation) + position;

    wxPen pen = *wxBLACK_PEN;
    pen.SetWidth(2);
    pen.SetCap(wxCAP_BUTT);
    graphics->SetPen(pen);
    graphics->StrokeLine(start.x, start.y, end.x, end.y);
}

/**
 * Map a value, t, from one range to another. The output value is clamped within the output range.
 * @param t The value to be transformed in the range [a, b]
 * @param a The minimum of t
 * @param b The maximum of t
 * @param c The minimum of the output value
 * @param d The maximum of the output value
 * @return An output value in the range [c, d]
 */
double VoltageMeter::MapValueRange(double t, double a, double b, double c, double d)
{
    // Transform ranges, then clamp
    t = (d-c)*(t-a)/(b-c) + c;
    t = t > d ? d : t;
    return t < c ? c : t;
}

/**
 * Reset this component to its initial state
 */
void VoltageMeter::Reset()
{
    mVoltage = 0;
    mCurrent = 0;
}
