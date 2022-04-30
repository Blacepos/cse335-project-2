/**
 * @file PowerSource.h
 * @author Joshua Austin
 *
 * A component which handles sending power to a sink
 */

#ifndef CANADIANEXPERIENCE_POWERSOURCE_H
#define CANADIANEXPERIENCE_POWERSOURCE_H

#include "BezierEnd.h"
#include "Polygon.h"

class PowerSink;

/**
 * A component which handles sending power to a sink
 */
class PowerSource : public BezierEnd {
private:
    /// Association to PowerSink
    PowerSink* mPowerSink = nullptr;

    /// The connector image for this sink
    cse335::Polygon mConnector;

    /// Store the size of connector
    double mSize = 10.0;

    /// The current capacity of this source
    double mAmperage = 100.0;
public:
    explicit PowerSource(std::wstring imagesDir, double amperage=100);

    /// Default constructor/disabled
    PowerSource() = delete;

    /// Copy constructor/deleted
    PowerSource(PowerSource const&) = delete;

    /// Assignment operator/disabled
    void operator=(const PowerSource&) = delete;

    double Power(double voltage);

    /**
     * The PowerSink associated with this source
     * @param sink The PowerSink
     */
    void SetPowerSink(PowerSink* sink) { mPowerSink = sink; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position);

    /**
     * Get the size of the connector image
     * @return The connector image size in pixels
     */
    double GetSize() const { return mSize; }

    /**
     * Get the capacity of this source
     * @return The capacity in amps
     */
     double GetAmperage() const { return mAmperage; }
};

#endif //CANADIANEXPERIENCE_POWERSOURCE_H
