/**
 * @file CableFactory.h
 * @author Joshua Austin
 *
 * Creates a cable between two connections (a source and a sink)
 */

#ifndef CANADIANEXPERIENCE_CABLEFACTORY_H
#define CANADIANEXPERIENCE_CABLEFACTORY_H

class LaboratoryActual;
class Cable;
class PowerSource;
class PowerSink;

/**
 * Creates a cable between two connections (a source and a sink)
 */
class CableFactory {
private:
    /// The lab to create the cable in
    std::shared_ptr<LaboratoryActual> mLab;

    /// The directory where images are stored
    std::wstring mImagesDir;
public:
    CableFactory(std::shared_ptr<LaboratoryActual> lab, std::wstring imagesDir);

    std::shared_ptr<Cable> Create(PowerSource* source, PowerSink* sink, int sinkSpeed=100, int sourceSpeed=100);
};

#endif //CANADIANEXPERIENCE_CABLEFACTORY_H
