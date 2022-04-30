/**
 * @file MugFactory.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "MugFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"

using namespace std;

/**
 * This is a factory method that creates the mug actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> MugFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"Mug");

    auto mug = make_shared<ImageDrawable>(L"Mug", imagesDir + L"/mug.png");
    mug->SetCenter(wxPoint(0,0));
    mug->SetPosition(wxPoint(0,0));
    actor->SetRoot(mug);


    actor->AddDrawable(mug);

    return actor;
}