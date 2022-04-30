/**
 * @file LabDrawable.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "LabDrawable.h"
#include "laboratory-api.h"
#include "Timeline.h"


/**
 * Constructor
 * @param name The name of this laboratory drawable
 * @param resourcesDir Directory that contains the resources for this application
 */
LabDrawable::LabDrawable(const std::wstring& name, std::wstring resourcesDir)
        : Drawable(name)
{
    LaboratoryFactory labFactory(resourcesDir);

    mLaboratory = labFactory.CreateLaboratory();
    mLaboratory->SetLocation(wxPoint(600, 800));
}

/**
 * Draw this laboratory drawable
 * @param graphics Graphics object to draw on
 */
void LabDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Setting the laboratory frame here is not too costly because
    // LabSwitch only makes updates if the frame is higher than or
    // less than the current frame of the laboratory
    int frame = mTimeline->GetCurrentFrame() - mStartFrame;
    if (frame < 0)
    {
        mLaboratory->SetLaboratoryFrame(0);
    }
    else
    {
        mLaboratory->SetLaboratoryFrame(frame);
    }

    mLaboratory->DrawLaboratory(graphics);
}

/**
 * Show the dialog box to set the laboratory number
 * @param window The parent window
 */
void LabDrawable::ShowDialogBox(wxWindow* window)
{
    LaboratoryDialog dlg(window, mLaboratory);
    if (dlg.ShowModal() == wxID_OK)
    {
        // A laboratory has been selected
    }
}

/**
 * Set the timeline for this lab drawable
 *
 * The laboratory needs to know the current time so it can animate internally
 * @param timeline A pointer to the timeline
 */
void LabDrawable::SetTimeline(Timeline* timeline)
{
    Drawable::SetTimeline(timeline);
    mLaboratory->SetFrameRate(timeline->GetFrameRate());
    mTimeline = timeline;
}

/**
 * Load the laboratory from XML
 * @param root The root xml node containing the needed information
 */
void LabDrawable::Load(wxXmlNode* root)
{
    mStartFrame = wxAtoi(root->GetAttribute(L"start_frame", L"0"));
    int number = wxAtoi(root->GetAttribute(L"laboratory_number", L"1"));
    mLaboratory->SetLaboratoryNumber(number);
}

/**
 * Save the laboratory to XML
 * @param root The root xml node where information will be saved
 */
void LabDrawable::Save(wxXmlNode* root)
{
    root->AddAttribute(L"start_frame", std::to_wstring(mStartFrame));
    root->AddAttribute(L"laboratory_number", std::to_wstring(mLaboratory->GetLaboratoryNumber()));
}
