/**
 * @file ActualLabFactory2.h
 * @author Joshua Austin
 *
 * Creates the first lab with components
 */

#ifndef CANADIANEXPERIENCE_ACTUALLABFACTORY2_H
#define CANADIANEXPERIENCE_ACTUALLABFACTORY2_H

class LaboratoryActual;

/**
 * Creates the first lab with components
 */
class ActualLabFactory2 {
private:
    /// The name of the directory in resources where images are stored
    std::wstring mImagesDir;

    /// The directory where resources are stored
    std::wstring mResourcesDir;
public:
    ActualLabFactory2(std::wstring resourcesDir, std::wstring imagesDir);
    std::shared_ptr<LaboratoryActual> CreateActualLab();
};

#endif //CANADIANEXPERIENCE_ACTUALLABFACTORY2_H
