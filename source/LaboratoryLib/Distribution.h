/**
 * @file Distribution.h
 * @author Joshua Austin
 *
 * A component that distributes power to multiple sinks
 */

#ifndef CANADIANEXPERIENCE_DISTRIBUTION_H
#define CANADIANEXPERIENCE_DISTRIBUTION_H

#include "PolyComponent.h"
#include "PowerSinkUser.h"
#include "PowerSink.h"
#include "PowerSource.h"

/**
 * A component that distributes power to multiple sinks
 */
class Distribution : public PolyComponent, public PowerSinkUser {
private:
    /// The sources for this distribution
    std::vector<std::unique_ptr<PowerSource>> mSources;

    /// The sink for this distribution
    PowerSink mSink;

    /// The position to place the next source
    int mNextSourcePosition = 0;

    /// The directory where images can be found
    std::wstring mImagesDir;
public:
    Distribution(std::wstring imagesDir, std::wstring name, double capacity=30);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    double Power(double voltage) override;

    /**
     * Get the power sink for this distribution
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSink() { return &mSink; }

    /**
     * Get a power source from this distribution
     * @param i Select which power source to get (starting from 0)
     * @return A pointer to the power source
     */
    PowerSource* GetPowerSource(int i) { return mSources.at(i).get(); }

    void AddSource(int amperage);

    void SetPosition(int x, int y) override;
};

#endif //CANADIANEXPERIENCE_DISTRIBUTION_H
