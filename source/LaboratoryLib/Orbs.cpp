/**
 * @file Orbs.cpp
 * @author Joshua Austin
 */
#include "pch.h"
#include "Orbs.h"

/// The image for the orbs
const std::wstring OrbsImage = L"/orbs.png";

/// Orb voltage for full power
const double OrbsVoltage = 1000;

/// Voltage below which the orbs do not spark.
const double OrbsMinVoltage = 250;

/// Orb amperage at full voltage
const double OrbsCurrent = 200;

/// Position on the Orbs where the power is connected
const wxPoint OrbsSinkPosition = wxPoint(-132, -110);

/// X offset to the left orb spark end in pixels
const int SparkOffset1X = -72;

/// X offset to the right orb spark end in pixels
const int SparkOffset2X = 75;

/// Y offset for the orb spark ends
const int SparkOffsetY = -45;

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 */
Orbs::Orbs(std::wstring imagesDir, std::wstring name)
    : PolyComponent(name), mSink(imagesDir, OrbsCurrent)
{
    SetImage(imagesDir + OrbsImage);
    BottomCenteredRectangle();

    mSink.SetPowerSinkUser(this);

    mSink.SetPosition(OrbsSinkPosition.x, OrbsSinkPosition.y);
    mSink.SetRotation(0.25);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Orbs::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->DrawPolygon(graphics, GetX() + position.x, GetY() + position.y + static_cast<int>(mOffset));

    if (mVoltage >= OrbsMinVoltage)
    {
        int x1 = GetX() + position.x + SparkOffset1X;
        int x2 = GetX() + position.x + SparkOffset2X;
        int y  = GetY() + position.y + static_cast<int>(mOffset) + SparkOffsetY;
        mSparky.Draw(graphics, x1, y, x2, y);
    }

    mSink.SetPosition(OrbsSinkPosition + GetPosition() + wxPoint(0, static_cast<int>(mOffset)));
    mSink.Draw(graphics, wxPoint(position.x, position.y));
}

/**
 * Power the orbs to turn on the sparks
 * @param voltage The input voltage
 * @return The current in response
 */
double Orbs::Power(double voltage)
{
    mVoltage = voltage;
    mSparky.SetIntensity(voltage / OrbsVoltage);
    return OrbsCurrent * voltage / OrbsVoltage;
}

/**
 * Drive the orbs to move them down
 * @param amount How far to move
 * @param duration How much time it should take in seconds to move to the destination
 */
void Orbs::Drive(double amount, double duration)
{
    mDestination = amount;
    mPixelsPerSecond = (amount - mOffset) / duration;
}

/**
 * Set the current time
 *
 * Updates the offset of the orbs and upcalls to Component
 * @param time The new time
 */
void Orbs::SetTime(double time)
{
    // record the time before the update
    double elapsed = GetTime();
    PolyComponent::SetTime(time);

    // calculate the elapsed time after the update
    elapsed = GetTime() - elapsed;

    // if rotating in the positive direction and we've passed the goal or the opposite case
    if (mOffset >= mDestination && mPixelsPerSecond > 0.0 ||
        mOffset <= mDestination && mPixelsPerSecond < 0.0)
    {
        mPixelsPerSecond = 0.0;
    }

    mOffset += elapsed * mPixelsPerSecond;

    mSparky.Update(elapsed);
    mSparky.SetTime(time);
}

/**
 * Reset the orbs
 */
void Orbs::Reset()
{
    mOffset = 0.0;
    mPixelsPerSecond = 0.0;
    mDestination = 0.0;
    mVoltage = 0.0;
    mSparky.Reset();
}

/**
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void Orbs::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mSink.SetPosition(mSink.GetPosition() + GetPosition());
}
