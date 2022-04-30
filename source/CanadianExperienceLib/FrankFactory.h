/**
 * @file FrankFactory.h
 * @author Charles Owen
 *
 * Factory class the builds the Frank character
 */

#ifndef CANADIANEXPERIENCE_FRANKFACTORY_H
#define CANADIANEXPERIENCE_FRANKFACTORY_H

class Actor;

/**
 * Factory class that builds the Harold character
 */
class FrankFactory {
public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //CANADIANEXPERIENCE_FRANKFACTORY_H
