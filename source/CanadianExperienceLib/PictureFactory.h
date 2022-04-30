/**
 * @file PictureFactory.h
 * @author Charles Owen
 *
 * A factory class that builds our picture.
 */

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

class Picture;
class LabDrawable;

/**
 * A factory class that builds our picture.
 */
class PictureFactory {
private:
    /// Store the lab drawable created so user can retrieve and interact with it
    std::shared_ptr<LabDrawable> mLabDrawable;
public:
    std::shared_ptr<Picture> Create(std::wstring resourcesDir);

    /**
     * Get a pointer to the created laboratory drawable
     * @return pointer to the lab drawable
     */
    std::shared_ptr<LabDrawable> GetLabDrawable() { return mLabDrawable; }
};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
