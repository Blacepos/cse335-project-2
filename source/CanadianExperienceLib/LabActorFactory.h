/**
 * @file LabActorFactory.h
 * @author Joshua Austin
 *
 * Create a laboratory actor factory
 */

#ifndef CANADIANEXPERIENCE_LABACTORFACTORY_H
#define CANADIANEXPERIENCE_LABACTORFACTORY_H

class Actor;
class LabDrawable;

/**
 * Create a laboratory actor factory
 */
class LabActorFactory {
private:
    /// Store the lab drawable created so user can retrieve and interact with it
    std::shared_ptr<LabDrawable> mLabDrawable;
public:
    std::shared_ptr<Actor> Create(std::wstring resourcesDir, std::wstring imagesDir);

    /**
     * Get a pointer to the created laboratory drawable
     * @return pointer to the lab drawable
     */
    std::shared_ptr<LabDrawable> GetLabDrawable() { return mLabDrawable; }
};

#endif //CANADIANEXPERIENCE_LABACTORFACTORY_H
