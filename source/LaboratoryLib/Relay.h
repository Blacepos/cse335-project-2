/**
 * @file Relay.h
 * @author Joshua Austin
 *
 * Electrically activated switch
 *
 * Relays voltage if the relay switch is powered with more than zero volts
 */

#ifndef CANADIANEXPERIENCE_RELAY_H
#define CANADIANEXPERIENCE_RELAY_H

#include "PolyComponent.h"
#include "PowerSource.h"
#include "PowerSink.h"
#include "PowerSinkUser.h"
#include "Polygon.h"

/**
 * Electrically activated switch
 *
 * Relays voltage if the relay switch is powered with more than zero volts
 */
class Relay : public PolyComponent, public PowerSinkUser {
private:
    /// The first power source (default)
    PowerSource mSource1;

    /// The second power source (active when switch is "on")
    PowerSource mSource2;

    /// The sink corresponding to the relayed power
    PowerSink mRelaySink;

    /// The sink corresponding to the switch activation
    PowerSink mSwitchSink;

    /// The image for the switch in the on position
    cse335::Polygon mOnImage;

    /// Class to receive power from the switch sink
    class Coil : public PowerSinkUser
    {
    public:
        /// The most recently recorded voltage
        double mVoltage = 0.0;

        double Power(double voltage) override;
    };

    /// The coil for this relay, receives power from the switch sink
    Coil mCoil;
public:
    Relay(std::wstring imagesDir, std::wstring name, int capacity=30);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    double Power(double voltage) override;

    /**
     * Get the relay sink for this switch
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSinkRelay() { return &mRelaySink; }

    /**
     * Get the switch sink for this switch
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSinkCoil() { return &mSwitchSink; }

    /**
     * Get the first power sink for this switch
     * @return A pointer to the power source
     */
    PowerSource* GetPowerSource1() { return &mSource1; }

    /**
     * Get the second power sink for this switch
     * @return A pointer to the power source
     */
    PowerSource* GetPowerSource2() { return &mSource2; }

    void SetPosition(int x, int y) override;
};

#endif //CANADIANEXPERIENCE_RELAY_H
