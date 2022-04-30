/**
 * @file Rheostat.h
 * @author Joshua Austin
 *
 * A component which outputs a variable percentage of the input voltage, responds to events
 */

#ifndef CANADIANEXPERIENCE_RHEOSTAT_H
#define CANADIANEXPERIENCE_RHEOSTAT_H

#include "PolyComponent.h"
#include "PowerSink.h"
#include "PowerSource.h"
#include "PowerSinkUser.h"
#include "Polygon.h"

/**
 * A component which outputs a variable percentage of the input voltage, responds to events
 */
class Rheostat : public PolyComponent, public PowerSinkUser {
private:
    /// The rotation of the knob which determines the voltage that will be sent out
    double mRotation = 0.0;

    /// How fast the knob should turn to reach the destination
    double mRotationsPerSecond = 0.0;

    /// The angle at knob the wheel should stop
    double mDestination = 0.0;

    /// The knob image
    cse335::Polygon mKnob;

    /// The sink for the rheostat
    PowerSink mSink;

    /// The source for the rheostat
    PowerSource mSource;
public:
    Rheostat(std::wstring imagesDir, std::wstring name, int capacity);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    void XmlEvent(wxXmlNode* node) override;

    double Power(double voltage) override;

    void Reset() override;

    void SetPosition(int x, int y) override;

    /**
     * Get the power sink for this rheostat
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSink() { return &mSink; }

    /**
     * Get the power sink for this rheostat
     * @return A pointer to the power source
     */
    PowerSource* GetPowerSource() { return &mSource; }

    void RotateTo(double angle, double seconds);

    void SetTime(double time) override;
};

#endif //CANADIANEXPERIENCE_RHEOSTAT_H
