/**
 * @file PowerSink.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "PowerSink.h"
#include "PowerSinkUser.h"

/// Image to use for power connections
const std::wstring ConnectionImage = L"/fitting.png";

/// Smallest size to display the connection
const int ConnectionMinimumSize = 10;

/// Used to compute the size of the connection image.
const int ConnectionCapacityDivisor = 100;

/**
 * Constructor
 * @param imagesDir The directory where images can be found
 * @param amperage The max current
 */
PowerSink::PowerSink(std::wstring imagesDir, double amperage)
{
    int size = ConnectionMinimumSize + amperage / ConnectionCapacityDivisor;

    mConnector.SetImage(imagesDir + ConnectionImage);
    mConnector.Rectangle(-size/2, 0, size, size);

    mSize = size;
}

/**
 * Sends power to a PowerSink
 * @param voltage The level of voltage to send
 * @return The current in response
 */
double PowerSink::Power(double voltage)
{
    // Would check if nullptr, but that should never happen if the components remember to set the user
    return mPowerSinkUser->Power(voltage);
}

/**
 * Draw the connector image
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void PowerSink::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    int x = GetPosition().x;
    int y = GetPosition().y;
    mConnector.SetRotation(GetRotation() + 0.5);
    mConnector.DrawPolygon(graphics, x + position.x, y + position.y);
}
