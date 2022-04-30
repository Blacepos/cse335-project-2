/**
 * @file FrankFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "FrankFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"
#include "ImageDrawable.h"
#include "HeadTop.h"


using namespace std;

/**
 * This is a factory method that creates our Frank actor.
 * @param imagesDir Directory that contains the images for this application
 * @return Pointer to an actor object.
 */
std::shared_ptr<Actor> FrankFactory::Create(std::wstring imagesDir)
{
    shared_ptr<Actor> actor = make_shared<Actor>(L"Frank");

    auto body = make_shared<ImageDrawable>(L"Body", imagesDir + L"/frank-body.png");
    body->SetCenter(wxPoint(100, 107));
    body->SetPosition(wxPoint(0, -200));
    actor->SetRoot(body);

    auto fleg = make_shared<ImageDrawable>(L"Far Leg", imagesDir + L"/frank-leg-far.png");
    fleg->SetCenter(wxPoint(30, 0));
    fleg->SetPosition(wxPoint(-30, 20));
    body->AddChild(fleg);

    auto nleg = make_shared<ImageDrawable>(L"Near Leg", imagesDir + L"/frank-leg-near.png");
    nleg->SetCenter(wxPoint(30, 9));
    nleg->SetPosition(wxPoint(-30, 20));
    body->AddChild(nleg);

    auto farm = make_shared<ImageDrawable>(L"Far Arm", imagesDir + L"/frank-arm-far.png");
    farm->SetCenter(wxPoint(24, 16));
    farm->SetPosition(wxPoint(25, -40));
    body->AddChild(farm);

    auto narm = make_shared<ImageDrawable>(L"Near Arm", imagesDir + L"/frank-arm-near.png");
    narm->SetCenter(wxPoint(50, 26));
    narm->SetPosition(wxPoint(0, -40));
    body->AddChild(narm);


    auto head = make_shared<ImageDrawable>(L"Head", imagesDir + L"/frank-head.png");
    head->SetCenter(wxPoint(68, 141));
    head->SetPosition(wxPoint(10, -90));
    body->AddChild(head);

    actor->AddDrawable(fleg);
    actor->AddDrawable(nleg);
    actor->AddDrawable(farm);

    actor->AddDrawable(body);
    actor->AddDrawable(head);
    actor->AddDrawable(narm);

    return actor;
}