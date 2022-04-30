/**
 * @file Cable.h
 * @author Joshua Austin
 *
 * Component that represents a cable
 */

#ifndef CANADIANEXPERIENCE_CABLE_H
#define CANADIANEXPERIENCE_CABLE_H

#include "PowerSink.h"
#include "PowerSinkUser.h"
#include "PowerSource.h"
#include "Component.h"
#include "BezierEnd.h"

/**
 * Component that represents a cable
 */
class Cable : public Component, public PowerSinkUser {
private:

    /// This cable's power source
    PowerSource mSource;

    /// This cable's power sink
    PowerSink mSink;

    /// The maximum capacity of the cable
    double mCapacity = 100.0;

    /// Stores information about a clamp on a bezier curve
    class Clamp : public BezierEnd
    {
    };

    /// The clamps for this cable
    std::vector<std::shared_ptr<Clamp>> mClamps;
public:
    Cable(std::wstring imagesDir, std::wstring name, double amperage=100.0);

    /// Default constructor/disabled
    Cable() = delete;

    /// Copy constructor/disabled
    Cable(const Cable&) = delete;

    /// Assignment operator/disabled
    void operator=(const Cable&) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    double Power(double voltage) override;

    /**
     * Get the power sink for this cable
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSink() { return &mSink; }

    /**
     * Get the first power sink for this cable
     * @return A pointer to the power source
     */
    PowerSource* GetPowerSource() { return &mSource; }

    void AddClamp(int x, int y, double rotation, double speed);

    /**
     * Set the current capacity of this cable
     * @param capacity The capacity in amps
     */
    void SetCapacity(double capacity) { mCapacity = capacity; }
};

#endif //CANADIANEXPERIENCE_CABLE_H
