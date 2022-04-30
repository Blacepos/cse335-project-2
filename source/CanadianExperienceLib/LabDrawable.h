/**
 * @file LabDrawable.h
 * @author Joshua Austin
 *
 * A drawable which displays a laboratory
 */

#ifndef CANADIANEXPERIENCE_LABDRAWABLE_H
#define CANADIANEXPERIENCE_LABDRAWABLE_H

#include "Drawable.h"
#include "laboratory-api.h"

class Timeline;

/**
 * A drawable which displays a laboratory
 */
class LabDrawable : public Drawable {
private:
    /// The laboratory to draw and interact with
    std::shared_ptr<Laboratory> mLaboratory;

    /// The frame the laboratory should start on
    int mStartFrame = 0;

    /// pointer to the timeline so the lab can know about the current time
    Timeline* mTimeline = nullptr;
public:
    LabDrawable(std::wstring const& name, std::wstring resourcesDir);

    /**
     * Determines if the LabDrawable has been clicked on
     *
     * The LabDrawable should not be interacted with by the user so this is always false
     * @param pos The position of the point to test
     * @return false
     */
    bool HitTest(wxPoint pos) override { return false; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void ShowDialogBox(wxWindow* window);

    void SetTimeline(Timeline* timeline) override;

    /**
     * Set the frame when the laboratory will begin playing normally
     * @param startFrame The frame number
     */
    void SetStartFrame(int startFrame) { mStartFrame = startFrame; }

    void Load(wxXmlNode* root);

    void Save(wxXmlNode* root);
};

#endif //CANADIANEXPERIENCE_LABDRAWABLE_H
