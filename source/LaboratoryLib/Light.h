/**
 * @file Light.h
 * @author Joshua Austin
 *
 * Light component in the lab
 */

#ifndef CANADIANEXPERIENCE_LIGHT_H
#define CANADIANEXPERIENCE_LIGHT_H

#include "PolyComponent.h"
#include "PowerSinkUser.h"
#include "Polygon.h"
#include "PowerSink.h"

/**
 * Light component in the lab
 */
class Light : public PolyComponent, public PowerSinkUser {
private:
    /// The overlay to show the light being turned on
    cse335::Polygon mOnImage;

    /// The most recently recorded voltage
    double mVoltage = 0;

    /// The sink for this light
    PowerSink mSink;
public:
    Light(std::wstring imagesDir, std::wstring name, std::wstring image, std::wstring onImage, int width);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    double Power(double voltage) override;

    /**
     * Get the power sink for this light
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSink() { return &mSink; }

    void Reset() override;

    void SetPosition(int x, int y) override;
};

#endif //CANADIANEXPERIENCE_LIGHT_H
