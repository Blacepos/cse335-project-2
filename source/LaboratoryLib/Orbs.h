/**
 * @file Orbs.h
 * @author Joshua Austin
 *
 * A lab component that sparks when powered and moves when driven
 */

#ifndef CANADIANEXPERIENCE_ORBS_H
#define CANADIANEXPERIENCE_ORBS_H

#include "PolyComponent.h"
#include "PowerSinkUser.h"
#include "PowerSink.h"
#include "MotionSinkUser.h"
#include "Sparky.h"

/**
 * A lab component that sparks when powered and moves when driven
 */
class Orbs : public PolyComponent, public PowerSinkUser, public MotionSinkUser {
private:
    /// Offset caused by being driven
    double mOffset = 0;

    /// How fast the orbs should move to reach the destination
    double mPixelsPerSecond = 0.0;

    /// The position at which the orbs should stop
    double mDestination = 0;

    /// The power sink for this light
    PowerSink mSink;

    /// handles the sparking between the orbs
    cse335::Sparky mSparky;

    /// The most recently recorded voltage
    double mVoltage = 0.0;
public:
    Orbs(std::wstring imagesDir, std::wstring name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    /**
     * Return the current offset from being driven
     * @return The current offset in pixels
     */
    int GetOffset() const { return mOffset; }

    double Power(double voltage) override;

    void Drive(double amount, double duration) override;

    /**
     * Get the power sink for this light
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSink() { return &mSink; }

    void SetTime(double time) override;

    void Reset() override;

    void SetPosition(int x, int y) override;
};

#endif //CANADIANEXPERIENCE_ORBS_H
