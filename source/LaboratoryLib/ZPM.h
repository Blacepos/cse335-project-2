/**
 * @file ZPM.h
 * @author Joshua Austin
 *
 * The laboratory power source
 */

#ifndef CANADIANEXPERIENCE_ZPM_H
#define CANADIANEXPERIENCE_ZPM_H

#include "PolyComponent.h"
#include "Polygon.h"
#include "PowerSource.h"

/**
 * The laboratory power source
 */
class ZPM : public PolyComponent {
private:
    /// The previously measured current
    double mCurrent = 0.0;

    /// The power source component for the zpm
    PowerSource mSource;
public:
    ZPM(std::wstring imagesDir, std::wstring name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    void SendPower();

    /**
     * Get the most recently recorded current
     * @return The current in amps
     */
    double GetCurrent() const { return mCurrent; }

    /**
     * Return a pointer to the power source
     * @return A pointer to the power source
     */
    PowerSource* GetPowerSource() { return &mSource; }

    void Reset() override;

    void SetPosition(int x, int y) override;
};

#endif //CANADIANEXPERIENCE_ZPM_H
