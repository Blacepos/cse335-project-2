/**
 * @file Distribution.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Distribution.h"

/// The image to use for the distribution panel
const std::wstring DistributionImage = L"/dist-6u.png";

/// Y location for the sources in pixels
const int SourcesY = -35;

/// X location for the first source in pixels
const int SourcesX = -35;

/// Spacing between the sources in pixels
const int SourcesSpacing = 15;

/// Location of the sink on the
const wxPoint DistributionSinkPosition = wxPoint(-48, -20);

/**
 * Constructor
 * @param imagesDir The directory where images are stored
 * @param name The name of this component
 * @param capacity The capacity of the sink connector
 */
Distribution::Distribution(std::wstring imagesDir, std::wstring name, double capacity)
        : PolyComponent(name), mImagesDir(imagesDir), mSink(imagesDir, capacity)
{
    SetImage(imagesDir + DistributionImage);
    BottomCenteredRectangle();

    mSink.SetPowerSinkUser(this);
    mSink.SetPosition(DistributionSinkPosition.x, DistributionSinkPosition.y);
    mSink.SetRotation(0.25);
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Distribution::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    GetPolygon()->DrawPolygon(graphics, position.x + GetX(), position.y + GetY());

    mSink.Draw(graphics, position);

    for (auto& source : mSources)
    {
        source->Draw(graphics, position);
    }
}

/**
 * Send power to each source
 * @param voltage How much power to send
 * @return The cumulative current in amps
 */
double Distribution::Power(double voltage)
{
    double total = 0;
    for (auto& source : mSources)
    {
        total += source->Power(voltage);
    }
    return total;
}

/**
 * Add a source to the distribution
 * @param amperage The capacity of the new connector
 */
void Distribution::AddSource(int amperage)
{
    auto source = std::make_unique<PowerSource>(mImagesDir, amperage);
    source->SetPosition(wxPoint(SourcesX + mNextSourcePosition, SourcesY) + GetPosition());
    source->SetRotation(0.5);
    mNextSourcePosition += SourcesSpacing;
    mSources.push_back(std::move(source));
//    PowerSource source(mImagesDir, amperage);
//    mSources.push_back(std::move(source));
}

/**
 * Set the position of this component
 * @param x The new x position
 * @param y The new y position
 */
void Distribution::SetPosition(int x, int y)
{
    PolyComponent::SetPosition(x, y);
    mSink.SetPosition(mSink.GetPosition() + GetPosition());
}