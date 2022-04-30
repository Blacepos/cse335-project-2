/**
 * @file LabActorFactory.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "LabActorFactory.h"
#include "LabDrawable.h"
#include "Actor.h"

using namespace std;

/**
 * This is a factory method that creates the laboratory actor.
 * @param imagesDir Directory that contains the images for this application
 * @param resourcesDir Directory that contains the resources for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> LabActorFactory::Create(std::wstring resourcesDir, std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"Laboratory");

    auto lab = make_shared<LabDrawable>(L"Laboratory Drawable", resourcesDir);
    lab->SetPosition(wxPoint(0, 0));
    lab->SetRotation(0);
    lab->SetStartFrame(0);

    actor->SetRoot(lab);

    mLabDrawable = lab;

    actor->AddDrawable(lab);

    return actor;
}
