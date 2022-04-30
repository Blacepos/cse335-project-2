/**
 * @file VoltageMeter.h
 * @author Joshua Austin
 *
 * Component which displays the voltage and current information going through it
 */

#ifndef CANADIANEXPERIENCE_VOLTAGEMETER_H
#define CANADIANEXPERIENCE_VOLTAGEMETER_H

#include "PolyComponent.h"
#include "PowerSinkUser.h"
#include "PowerSink.h"
#include "PowerSource.h"

/**
 * Component which displays the voltage and current information going through it
 */
class VoltageMeter : public PolyComponent, public PowerSinkUser {
private:
    /// The source for this distribution
    PowerSource mSource;

    /// The sink for this distribution
    PowerSink mSink;

    /// The current recorded in the meter
    double mCurrent = 0;

    /// The voltage recorded in the meter
    double mVoltage = 0;

    void DrawNeedle(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position, double rotation);

    static double MapValueRange(double t, double a, double b, double c, double d);

public:
    VoltageMeter(std::wstring imagesDir, std::wstring name, int capacity=30);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    double Power(double voltage) override;

    /**
     * Get the power sink for this voltage meter
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSink() { return &mSink; }

    /**
     * Get the power source for this voltage meter
     * @return A pointer to the power source
     */
    PowerSource* GetPowerSource() { return &mSource; }

    void SetPosition(int x, int y) override;

    void Reset() override;
};

#endif //CANADIANEXPERIENCE_VOLTAGEMETER_H
