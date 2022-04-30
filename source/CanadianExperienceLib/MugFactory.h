/**
 * @file MugFactory.h
 * @author Joshua Austin
 *
 * Creates a mug Actor
 */

#ifndef CANADIANEXPERIENCE_MUGFACTORY_H
#define CANADIANEXPERIENCE_MUGFACTORY_H

class Actor;

/**
 * Creates a mug Actor
 */
class MugFactory {
public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //CANADIANEXPERIENCE_MUGFACTORY_H
