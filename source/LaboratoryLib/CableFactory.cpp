/**
 * @file CableFactory.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "CableFactory.h"

#include "PowerSource.h"
#include "PowerSink.h"
#include "Cable.h"
#include "GraphicsHelper.h"
#include "LaboratoryActual.h"

using namespace cse335;

/**
 * Constructor
 * @param lab A pointer to the lab so the cable is added automaticall
 * @param imagesDir The directory where images are stored
 */
CableFactory::CableFactory(std::shared_ptr<LaboratoryActual> lab, std::wstring imagesDir)
    : mLab(lab), mImagesDir(imagesDir)
{
}

/**
 * Create a cable between two sources
 * @param source The source to connect to
 * @param sink The sink to connect to
 * @param sinkSpeed The bezier curve speed of the cable sink
 * @param sourceSpeed The bezier curve speed of the cable source
 * @return A pointer to the cable for adding clamps
 */
std::shared_ptr<Cable> CableFactory::Create(PowerSource* source, PowerSink* sink, int sinkSpeed, int sourceSpeed)
{
    auto cable = std::make_shared<Cable>(mImagesDir, L"cable", source->GetAmperage());

    // convenience variables
    auto cableSink = cable->GetPowerSink();
    auto cableSource = cable->GetPowerSource();

    // make the connection
    source->SetPowerSink(cable->GetPowerSink());
    cable->GetPowerSource()->SetPowerSink(sink);

    //
    // rotate and position the cable's source and sink
    //
    auto cableSinkOffset = GraphicsHelper::ToIntVector(source->GetRotation(), source->GetSize());
    auto cableSourceOffset = GraphicsHelper::ToIntVector(sink->GetRotation(), sink->GetSize());

    // instead of setting position directly, set the cable ends to follow the given source and sink
    cableSink->SetFollowee(source, -cableSinkOffset);
    cableSource->SetFollowee(sink, -cableSourceOffset);

    // may need to add 0.5 (and above)
    cableSink->SetRotation(source->GetRotation() + 0.5);
    cableSource->SetRotation(sink->GetRotation());

    cableSink->SetSpeed(sinkSpeed);
    cableSource->SetSpeed(sourceSpeed);

    mLab->AddComponent(cable);

    return cable;
}


