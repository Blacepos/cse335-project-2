/**
 * @file PowerSink.h
 * @author Joshua Austin
 *
 * Handles receiving power and telling a lab component
 */

#ifndef CANADIANEXPERIENCE_POWERSINK_H
#define CANADIANEXPERIENCE_POWERSINK_H

#include "BezierEnd.h"
#include "Polygon.h"

class PowerSinkUser;

/**
 * Handles receiving power and telling a lab component
 */
class PowerSink : public BezierEnd {
private:
    /// The lab component which will receive the power
    PowerSinkUser* mPowerSinkUser = nullptr;

    /// The connector image for this sink
    cse335::Polygon mConnector;

    /// Store the size of connector
    double mSize = 10.0;
public:
    explicit PowerSink(std::wstring imagesDir, double amperage=100);

    /// Default constructor/deleted
    PowerSink() = delete;

    /// Copy constructor/deleted
    PowerSink(PowerSink const&) = delete;

    /// Assignment operator/disabled
    void operator=(const PowerSink&) = delete;

    double Power(double voltage);

    /**
     * Set the lab component which can be powered
     * @param sink The lab component which is a power sink
     */
    void SetPowerSinkUser(PowerSinkUser* sink) { mPowerSinkUser = sink; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position);

    /**
     * Get the size of the connector image
     * @return The connector image size in pixels
     */
    double GetSize() const { return mSize; }
};

#endif //CANADIANEXPERIENCE_POWERSINK_H
