/**
 * @file Light.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Light.h"

/// Light voltage for full illumination
const double LightVoltage = 1000;

/// Light amperage at full voltage
const double LightCurrent = 100;

/**
 *
 * @param imagesDir Directory that contains the images for this application
 * @param name The name of this component
 * @param image The image of the light
 * @param onImage The image to overlay when the light is on
 * @param width The width of the image
 */
Light::Light(std::wstring imagesDir, std::wstring name, std::wstring image, std::wstring onImage, int width)
    : PolyComponent(name), mSink(imagesDir, LightCurrent)
{
    SetImage(imagesDir + image);
    Rectangle(-width/2, 0, width);

    mOnImage.SetImage(imagesDir + onImage);
    mOnImage.Rectangle(-width/2, 0, width);

    mSink.SetPowerSinkUser(this);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Light::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->DrawPolygon(graphics, GetX() + position.x, GetY() + position.y);
    if (mVoltage > 0)
    {
        mOnImage.DrawPolygon(graphics, GetX() + position.x, GetY() + position.y);
    }

    mSink.Draw(graphics, position);
}

/**
 * Send power to this component
 * @param voltage How much power is received in volts
 * @return The current in amps
 */
double Light::Power(double voltage)
{
    mVoltage = voltage;
    mOnImage.SetOpacity(voltage / LightVoltage);
    return voltage / LightVoltage * LightCurrent;
}

/**
 * Reset the light
 */
void Light::Reset()
{
    mVoltage = 0.0;
}

/**
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void Light::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mSink.SetPosition(mSink.GetPosition() + GetPosition());
}
