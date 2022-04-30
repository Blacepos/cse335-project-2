/**
 * @file LabSwitch.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "LabSwitch.h"
#include "LaboratoryActual.h"
#include "ActualLabFactory1.h"
#include "ActualLabFactory2.h"

/**
 * Constructor
 * @param resourcesDir Directory that contains the resources for this application
 * @param imagesDir Directory that contains the images for this application
 */
LabSwitch::LabSwitch(std::wstring resourcesDir, std::wstring imagesDir)
        : mResourcesDir(resourcesDir), mImagesDir(imagesDir)
{
}

/**
 * Draw the laboratory
 * @param graphics The graphics context to draw to
 */
void LabSwitch::DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics)
{
    mLab->DrawLaboratory(graphics, mLabLocation);
}

/**
 * Change the laboratory number
 *
 * Uses a factory to create the lab
 * @param laboratory Which number to load
 */
void LabSwitch::SetLaboratoryNumber(int laboratory)
{
    // Create with Factory
    if (laboratory == 1)
    {
        ActualLabFactory1 factory(mResourcesDir, mImagesDir);
        mLab = factory.CreateActualLab();
    }
    else if (laboratory == 2)
    {
        ActualLabFactory2 factory(mResourcesDir, mImagesDir);
        mLab = factory.CreateActualLab();
    }

    SetLaboratoryFrame(0);
}

/**
 * Get which lab this is
 * @return The lab number
 */
int LabSwitch::GetLaboratoryNumber()
{
    return mLab->GetLaboratoryNumber();
}

/**
 * Set the laboratory frame
 * @param frame The frame
 */
void LabSwitch::SetLaboratoryFrame(int frame)
{
    if (frame < mFrame)
    {
        // We are going backwards in time,
        // reset to the beginning
        mFrame = -1;
        Reset();
    }

    // loop one frame at a time until the lab is caught up
    while (mFrame < frame)
    {
        mFrame++;
        mTime = static_cast<double>(mFrame) / static_cast<double>(mFrameRate);
        //SetTime(mTime);
        mLab->SetLaboratoryTime(mTime);
    }
}

/**
 * Reset the lab to time 0
 */
void LabSwitch::Reset()
{
//    // The simplest solution for now, very slow
//    SetLaboratoryNumber(mLab->GetLaboratoryNumber());
    mTime = -1;
    mLab->Reset();
}
