/**
 * @file LabSwitch.h
 * @author Joshua Austin
 *
 * The implementation of a laboratory
 */

#ifndef CANADIANEXPERIENCE_LABSWITCH_H
#define CANADIANEXPERIENCE_LABSWITCH_H

#include "Laboratory.h"

class LaboratoryActual;

/**
 * The implementation of a laboratory
 */
class LabSwitch : public Laboratory {
private:
    /// The directory where resources can be found
    std::wstring mResourcesDir;

    /// The directory where images can be found
    std::wstring mImagesDir;

    /// The frame rate of the laboratory
    int mFrameRate = 30;

    /// The current time of the laboratory
    double mTime = 0;

    /// The current frame of the lab for convenience
    int mFrame = 0;

    /// The position of the lab
    wxPoint mLabLocation = wxPoint(0, 0);

    /// The current laboratory
    std::shared_ptr<LaboratoryActual> mLab;
public:
    /// Constructor
    LabSwitch(std::wstring resourcesDir, std::wstring imagesDir);

    /// Default constructor/disabled
    LabSwitch() = delete;

    /// Copy constructor/disabled
    LabSwitch(const LabSwitch&) = delete;

    /// Assignment operator/disabled
    void operator=(const LabSwitch&) = delete;

    void DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetLaboratoryNumber(int laboratory) override;

    int GetLaboratoryNumber() override;

    void SetLaboratoryFrame(int frame) override;

    /**
     * Set the position of the lab
     * @param location The position
     */
    void SetLocation(wxPoint location) override { mLabLocation = location; }

    /**
     * Get the position of the lab
     * @return The position
     */
    wxPoint GetLocation() override { return mLabLocation; }

    /**
     * Set the frame rate of the lab
     * @param frameRate The frame rate
     */
    void SetFrameRate(double frameRate) override { mFrameRate = frameRate; }

    /**
     * Get the current laboratory time.
     * @return Laboratory time in seconds
     */
    double GetLaboratoryTime() override { return mTime; }

    void Reset();
};

#endif //CANADIANEXPERIENCE_LABSWITCH_H
