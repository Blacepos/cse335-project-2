/**
 * @file ActualLabFactory1.h
 * @author Joshua Austin
 *
 * Creates the first lab with components
 */

#ifndef CANADIANEXPERIENCE_ACTUALLABFACTORY1_H
#define CANADIANEXPERIENCE_ACTUALLABFACTORY1_H

class LaboratoryActual;

/**
 * Creates the first lab with components
 */
class ActualLabFactory1 {
private:
    /// The name of the directory in resources where images are stored
    std::wstring mImagesDir;

    /// The directory where resources are stored
    std::wstring mResourcesDir;
public:
    ActualLabFactory1(std::wstring resourcesDir, std::wstring imagesDir);

    std::shared_ptr<LaboratoryActual> CreateActualLab();
};

#endif //CANADIANEXPERIENCE_ACTUALLABFACTORY1_H
