/**
 * @file Relay.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Relay.h"

/// The image to use for the switch on
const std::wstring RelayOnImage = L"/relay-on.png";

/// The image to use for the switch on
const std::wstring RelayOffImage = L"/relay-off.png";

/// X position of the relay switch input in pixels
const int RelaySinkX = -30;

/// X position of the relay coil input in pixels
const int RelaySinkCoilX = 0;

/// X position of the relay deactivated output in pixels
const int RelaySourceOffX= 15;

/// X position of the relay activated output in pixels
const int RelaySourceOnX = 30;

/// How large we are drawing the relay
const int RelaySize = 80;

/// Y position of the relay relative to the panel it is mounted on.
const int RelayY = -20;

/// Relay resistance
const double RelayCoilResistance = 100.0;

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 * @param capacity The capacity of the connectors
 */
Relay::Relay(std::wstring imagesDir, std::wstring name, int capacity)
    :PolyComponent(name), mRelaySink(imagesDir, capacity), mSwitchSink(imagesDir, capacity),
    mSource1(imagesDir, capacity), mSource2(imagesDir, capacity)
{
    SetImage(imagesDir + RelayOffImage);
    Rectangle(-RelaySize/2, 0, RelaySize);

    mOnImage.SetImage(imagesDir + RelayOnImage);
    mOnImage.Rectangle(-RelaySize/2, 0, RelaySize);

    mRelaySink.SetPowerSinkUser(this);
    mSwitchSink.SetPowerSinkUser(&mCoil);

    mRelaySink.SetPosition(RelaySinkX, RelayY);
    mSwitchSink.SetPosition(RelaySinkCoilX, RelayY);
    mSource1.SetPosition(RelaySourceOffX, RelayY);
    mSource2.SetPosition(RelaySourceOnX, RelayY);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Relay::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    if (mCoil.mVoltage > 0)
    {
        mOnImage.DrawPolygon(graphics, GetX() + position.x, GetY() + position.y + RelayY);
    }
    else
    {
        GetPolygon()->DrawPolygon(graphics, GetX() + position.x, GetY() + position.y + RelayY);
    }

    mRelaySink.Draw(graphics, position);
    mSwitchSink.Draw(graphics, position);
    mSource1.Draw(graphics, position);
    mSource2.Draw(graphics, position);
}

/**
 * Send power to one of the sources
 *
 * Both sources are powered, but one is given 0 volts
 * @param voltage How much power to send
 * @return The current in response
 */
double Relay::Power(double voltage)
{
    // send power to the first source until the coil is powered with more than 0 volts
    if (mCoil.mVoltage > 0)
    {
        return mSource1.Power(0.0) + mSource2.Power(voltage);
    }
    else
    {
        return mSource1.Power(voltage) + mSource2.Power(0.0);
    }
}

/**
 * Send power to the coil of the relay
 * @param voltage How much power is received in volts
 * @return The current caused by the coil (1 amp per 100 volts)
 */
double Relay::Coil::Power(double voltage)
{
    mVoltage = voltage;
    return voltage / RelayCoilResistance;
}

/**
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void Relay::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mRelaySink.SetPosition(mRelaySink.GetPosition() + GetPosition());
    mSwitchSink.SetPosition(mSwitchSink.GetPosition() + GetPosition());
    mSource1.SetPosition(mSource1.GetPosition() + GetPosition());
    mSource2.SetPosition(mSource2.GetPosition() + GetPosition());
}
