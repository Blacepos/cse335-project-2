/**
 * @file LaboratoryFactory.h
 *
 * @author Charles Owen
 *
 * Laboratory factory class. Creates Laboratory objects
 *
 * You should not have any reason to change this header file!
 */

#ifndef CANADIANEXPERIENCE_LABORATORYFACTORY_H
#define CANADIANEXPERIENCE_LABORATORYFACTORY_H

#include <memory>

class Laboratory;

/**
 * Laboratory factory class. Creates Laboratory objects
 */
class LaboratoryFactory
{
private:
    /// The resources directory
    std::wstring mResourcesDir;

public:
    LaboratoryFactory(std::wstring resourcesDir);

    // Do not change the return type for CreateLaboratory!
    std::shared_ptr<Laboratory> CreateLaboratory();
};

#endif //CANADIANEXPERIENCE_MACHIN0FACTORY_H