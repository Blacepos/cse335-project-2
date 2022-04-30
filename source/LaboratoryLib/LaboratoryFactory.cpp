/**
 * @file LaboratoryFactory.cpp
 *
 * @author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "LaboratoryFactory.h"
#include "Laboratory.h"
#include "LabSwitch.h"

/// The directory where images can be found
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory to load images from
 */
LaboratoryFactory::LaboratoryFactory(std::wstring resourcesDir) :mResourcesDir(resourcesDir)
{
}


/**
 * Create a laboratory object
 *
 * Do not change the return type of this function!
 *
 * @return Object of type Laboratory
 */
std::shared_ptr<Laboratory> LaboratoryFactory::CreateLaboratory()
{
    auto lab = std::make_shared<LabSwitch>(mResourcesDir, mResourcesDir + ImagesDirectory);
    lab->SetLaboratoryNumber(1);
    return lab;
}


