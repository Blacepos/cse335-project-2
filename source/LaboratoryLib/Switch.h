/**
 * @file Switch.h
 * @author Joshua Austin
 *
 * A switch that can toggle output
 */

#ifndef CANADIANEXPERIENCE_SWITCH_H
#define CANADIANEXPERIENCE_SWITCH_H

#include "PolyComponent.h"
#include "PowerSource.h"
#include "PowerSink.h"
#include "PowerSinkUser.h"
#include "Polygon.h"

/**
 * A switch that can toggle output
 */
class Switch : public PolyComponent, public PowerSinkUser {
private:
    /// The first power source (default)
    PowerSource mSource1;

    /// The second power source (active when switch is "on")
    PowerSource mSource2;

    /// The sink for this switch
    PowerSink mSink;

    /// The image for the switch in the on position
    cse335::Polygon mOnImage;

    /// The state of the switch
    bool mOn = false;

    /// Where to place the sources and sinks, default is left
    bool mRight = false;
public:
    Switch(std::wstring imagesDir, std::wstring name, int capacity, bool rightSide=false);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    void XmlEvent(wxXmlNode* node) override;

    double Power(double voltage) override;

    /**
     * Get the power sink for this switch
     * @return A pointer to the power sink
     */
    PowerSink* GetPowerSink() { return &mSink; }

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

    /**
     * Set the switch to be on
     * @param state true if on
     */
    void SetOn(bool state) { mOn = state; }

    void Reset() override;

    void SetPosition(int x, int y) override;
};

#endif //CANADIANEXPERIENCE_SWITCH_H
