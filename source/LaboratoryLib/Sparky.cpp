/**
 * @file Sparky.cpp
 * @author Charles Owen
 *
 * Uses ideas from:
 * https://gamedevelopment.tutsplus.com/tutorials/how-to-generate-shockingly-good-2d-lightning-effects--gamedev-2681
 */

#include "pch.h"

#include <cmath>
#include "Sparky.h"

using namespace cse335;

/// Maximum intensity standard deviation
const double MaxIntensity = 100.0;

/**
 * Constructor
 */
Sparky::Sparky()
{
    // Create a random number seed to use
    std::random_device rd{};
    mSeed = rd();

    Reset();
}

/**
 * Reset the system to time zero
 */
void Sparky::Reset()
{
    mRnd.seed(mSeed);
    mLastTime = 0;
}

/**
 * Draw the sparking/lightning
 * @param graphics Graphics device to draw on
 * @param x1 From X location
 * @param y1 From Y location
 * @param x2 To X location
 * @param y2 To Y location
 */
void Sparky::Draw(std::shared_ptr<wxGraphicsContext> graphics, double x1, double y1, double x2, double y2)
{
    if(mIntensity < 0.01)
    {
        return;
    }

    graphics->PushState();

    //
    // To simply the logic, we assume the bolt goes from
    // (0,0) to (length,0) rather than and arbitrary angles.
    //
    graphics->Translate(x1, y1);

    auto dx = x2 - x1;
    auto dy = y2 - y1;
    auto length = sqrt(dx * dx + dy * dy);

    auto angle = atan2(dy, dx);
    graphics->Rotate(angle);

    if(mBolt.size() == 0)
    {
        // Create the lightning bolt
        mBolt = CreateBolt(length);
    }

    wxColour color1(mColour.Red(), mColour.Green(), mColour.Blue(), 10);
    wxPen pen1(color1, 20);
    graphics->SetPen(pen1);

    for(auto& line: mBolt)
    {
        line.Draw(graphics);
    }

    wxColour color2(mColour.Red(), mColour.Green(), mColour.Blue(), 20);
    wxPen pen2(color2, 10);
    graphics->SetPen(pen2);

    for(auto& line: mBolt)
    {
        line.Draw(graphics);
    }

    wxPen penRed(mColour, 2);
    graphics->SetPen(penRed);

    for(auto& line: mBolt)
    {
        line.Draw(graphics);
    }

    graphics->PopState();
}

/**
 * Create a lightning bolt.
 *
 * This is normalized from (0, 0) to (length, 0)
 *
 * @param length Length of the bolt.
 * @return
 */
std::vector<Sparky::Line> Sparky::CreateBolt(double length)
{
    wxPoint2DDouble start(0,0);
    wxPoint2DDouble end(length, 0);

    std::vector<Sparky::Line> lines;

    int numPositions = length / 4;

    std::vector<double> positions;
    std::uniform_real_distribution<> dist(0, 1);
    for(int i=0; i<numPositions; i++)
    {
        positions.push_back(dist(mRnd));
    }

    positions.push_back(0);

    std::sort(positions.begin(), positions.end());

    wxPoint2DDouble tangent(length, 0);
    wxPoint2DDouble normal(0, 1);

    wxPoint2DDouble prevPoint = start;
    float prevDisplacement = 0;
    for (int i = 1; i < positions.size(); i++)
    {
        double pos = positions[i];

        // The range of change we allow is dependent on
        // the distance we are travelling along the line
        double deltaStandardDeviation = (pos - positions[i-1]) * mIntensity * MaxIntensity;

        std::normal_distribution<> dist(0, deltaStandardDeviation);
        double displacement = prevDisplacement + dist(mRnd);

        // A quadratic envelope, so that points near the ends have less
        // possible range, so we converge to the end points.
        double envelope = -4 * (pos * pos - pos);

        // Create the point and add to the line
        wxPoint2DDouble point(pos * length, displacement * envelope);
        lines.push_back({prevPoint, point});

        prevPoint = point;
        prevDisplacement = displacement;
    }

    lines.push_back({prevPoint, end});

    return lines;
}

/**
 * Set the current time. This function keeps track of time changes
 * and calls Update with the elapsed time change. Either function can
 * be used.
 *
 * Call SetTime or call Update. Don't call bath!
 *
 * @param time Time in seconds
 */
void Sparky::SetTime(double time)
{
    double elapsed = time - mLastTime;
    mLastTime = time;

    Update(elapsed);
}

/**
 * Update the
 * @param elapsed
 */
void Sparky::Update(double elapsed)
{
    if(elapsed > 0)
    {
        mBolt.clear();
    }
}

/**
 * Line segment constructor
 * @param a Starting point for the line segment
 * @param b Ending point for the line segment
 */
Sparky::Line::Line(wxPoint2DDouble a, wxPoint2DDouble b) :
    mA(a), mB(b)
{
}

/**
 * Actually draw a sparky line segment.
 * @param graphics Graphics context to draw the line segement on
 */
void Sparky::Line::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->StrokeLine(mA.m_x, mA.m_y, mB.m_x, mB.m_y);
}


