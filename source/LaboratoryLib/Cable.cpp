/**
 * @file Cable.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "Cable.h"
#include "GraphicsHelper.h"

/// Smallest possible cable size
const int CableMinimumWidth = 3;

/// The width of the cable line is CableMinimumWidth
/// plus capacity / CableCapacityDivisor
const int CableCapacityDivisor = 200;

/// The cable color
const wxColour CableColor = wxColour(40, 40, 40);

/**
 * Constructor
 * @param imagesDir The directory where images can be found
 * @param name The name of this component
 * @param amperage The capacity of this cable
 */
Cable::Cable(std::wstring imagesDir, std::wstring name, double amperage)
        : Component(name), mSink(imagesDir), mSource(imagesDir)
{
    mSink.SetPowerSinkUser(this);
    mCapacity = amperage;
}

/**
 * Draw this component
 * @param graphics The context to draw on
 * @param position The position at which to draw the object
 */
void Cable::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    int width = int(CableMinimumWidth + mCapacity / CableCapacityDivisor);
    auto pen = wxPen(CableColor, width);
    pen.SetCap(wxCAP_BUTT);
    graphics->SetPen(pen);
    auto path = graphics->CreatePath();

    if (!mClamps.empty())
    {
        // sink and first clamp

        wxPoint p1 = mSink.GetP1() + position;
        wxPoint p2 = mSink.GetP2() + position;
        wxPoint p3 = mClamps.front()->GetP3() + position;
        wxPoint p4 = mClamps.front()->GetP4() + position;
        path.MoveToPoint(p1.x, p1.y);
        path.AddCurveToPoint(p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);

        for (int i = 1; i < mClamps.size(); ++i)
        {
            p1 = mClamps[i-1]->GetP1() + position;
            p2 = mClamps[i-1]->GetP2() + position;
            p3 = mClamps[i]->GetP3() + position;
            p4 = mClamps[i]->GetP4() + position;
            path.MoveToPoint(p1.x, p1.y);
            path.AddCurveToPoint(p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
        }

        // last clamp and source
        p1 = mClamps.back()->GetP1() + position;
        p2 = mClamps.back()->GetP2() + position;
        p3 = mSource.GetP3() + position;
        p4 = mSource.GetP4() + position;
        path.MoveToPoint(p1.x, p1.y);
        path.AddCurveToPoint(p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
    }
    else
    {
        // sink and source
        wxPoint p1 = mSink.GetP1() + position;
        wxPoint p2 = mSink.GetP2() + position;
        wxPoint p3 = mSource.GetP3() + position;
        wxPoint p4 = mSource.GetP4() + position;
        path.MoveToPoint(p1.x, p1.y);
        path.AddCurveToPoint(p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
    }
    graphics->StrokePath(path);
}

/**
 * Send power across the cable
 * @param voltage How much power to send
 * @return The current in response
 */
double Cable::Power(double voltage)
{
    return mSource.Power(voltage);
}

/**
 * Add a clamp to the cable
 * @param x The x position of the clamp
 * @param y The y position of the clamp
 * @param rotation The rotation of the clamp (in whole rotations)
 * @param speed The speed of the clamp (affects the bezier curve)
 */
void Cable::AddClamp(int x, int y, double rotation, double speed)
{
    auto clamp = std::make_shared<Clamp>();
    clamp->SetPosition(x, y);
    clamp->SetRotation(rotation);
    clamp->SetSpeed(speed);
    mClamps.push_back(std::move(clamp));
}
