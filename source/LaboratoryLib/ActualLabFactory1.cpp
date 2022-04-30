/**
 * @file ActualLabFactory1.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "ActualLabFactory1.h"
#include "LaboratoryActual.h"
#include "Shape.h"
#include "ZPM.h"
#include "EquipmentRack.h"
#include "Light.h"
#include "Distribution.h"
#include "Switch.h"
#include "Winch.h"
#include "Orbs.h"
#include "CableFactory.h"
#include "Cable.h"

using namespace std;

/**
 * Constructor
 * @param resourcesDir Path to program resources directory
 * @param imagesDir Path to the images directory
 */
ActualLabFactory1::ActualLabFactory1(std::wstring resourcesDir, std::wstring imagesDir)
        : mResourcesDir(resourcesDir), mImagesDir(imagesDir)
{
}

/**
 * Create a lab 1 instance
 * @return A shared pointer to a lab
 */
std::shared_ptr<LaboratoryActual> ActualLabFactory1::CreateActualLab()
{
    auto lab = make_shared<LaboratoryActual>(1);

    const int Rack1X = -350;
    const int Rack2X = 350;
    const int RackY = -130;

    // create stuff
    auto background = std::make_shared<Shape>(L"Background");
    background->SetImage(mImagesDir + L"/laboratory.jpg");
    background->Rectangle(-600, 0);
    lab->AddComponent(background);

    auto zpm = std::make_shared<ZPM>(mImagesDir, L"ZPM");
    zpm->SetPosition(-550, -130);
    lab->AddComponent(zpm);
    lab->SetZPM(zpm);

    auto rack1 = std::make_shared<EquipmentRack>(mImagesDir, L"Rack 1");
    rack1->SetPosition(Rack1X, RackY);
    lab->AddComponent(rack1);

    rack1->AddBlankPanel(mImagesDir + L"/2u.png", 0);
    rack1->AddBlankPanel(mImagesDir + L"/2u.png", 2);
    rack1->AddBlankPanel(mImagesDir + L"/1u.png", 4);
    rack1->AddBlankPanel(mImagesDir + L"/12u.png", 11);
    rack1->AddBlankPanel(mImagesDir + L"/6u.png", 29);

    auto rack2 = std::make_shared<EquipmentRack>(mImagesDir, L"Rack 2");
    rack2->SetPosition(Rack2X, RackY);
    lab->AddComponent(rack2);

    rack2->AddBlankPanel(mImagesDir + L"/5u.png", 0);
    rack2->AddBlankPanel(mImagesDir + L"/radio-6u.png", 17);
    rack2->AddBlankPanel(mImagesDir + L"/6u.png", 23);
    rack2->AddBlankPanel(mImagesDir + L"/6u.png", 29);

    //
    // Lights
    //
    auto light1 = make_shared<Light>(mImagesDir, L"Light 1",
            L"/light1.png", L"/light1on.png", 200);
    auto light1sink = light1->GetPowerSink();
    light1sink->SetRotation(0.33);
    light1sink->SetPosition(-42, -70);
    light1->SetPosition(180, -450);
    lab->AddComponent(light1);

    auto light2 = make_shared<Light>(mImagesDir, L"Light 2",
            L"/light2.png", L"/light2on.png", 100);
    auto light2sink = light2->GetPowerSink();
    light2sink->SetRotation(0.12);
    light2sink->SetPosition(-35, -13);
    light2->SetPosition(-250, -450);
    lab->AddComponent(light2);

    auto light3 = make_shared<Light>(mImagesDir, L"Light 3",
            L"/floor-lamp-off.png", L"/floor-lamp-on.png", 32);
    auto light3sink = light3->GetPowerSink();
    light3sink->SetRotation(0.25);
    light3sink->SetPosition(-2, -15);
    light3->SetPosition(Rack1X+120, -130);
    lab->AddComponent(light3);


    // PANELS
    auto panel = make_shared<Distribution>(mImagesDir, L"Distribution 1", 1000);
    rack1->SetPanelPosition(panel, 5);
    lab->AddComponent(panel);

    panel->AddSource(100);
    panel->AddSource(200);
    panel->AddSource(500);

    auto panel2 = make_shared<Distribution>(mImagesDir, L"Distribution 2", 100);

    rack1->SetPanelPosition(panel2, 23);
    lab->AddComponent(panel2);

    panel2->AddSource(100);
    panel2->AddSource(100);

    // SWITCHES
    auto switch1 = make_shared<Switch>(mImagesDir, L"switch1", 100);
    rack1->SetPanelPosition(switch1, 11, -25);
    lab->AddComponent(switch1);

    auto switch2 = make_shared<Switch>(mImagesDir, L"switch2", 200, true);
    rack1->SetPanelPosition(switch2, 11, 25);
    lab->AddComponent(switch2);

    //
    // Winch and orbs
    //
    auto winch = make_shared<Winch>(mImagesDir, L"winch");
    rack2->SetPanelPosition(winch, 5);
    lab->AddComponent(winch);

    auto orbs = make_shared<Orbs>(mImagesDir, L"orbs");
    orbs->SetPosition(-50, -800);
    lab->AddComponent(orbs);

    winch->GetMotionSource()->SetScale(200);
    winch->GetMotionSource()->SetMotionSinkUser(orbs.get());

    //
    // Connections
    //
    CableFactory cableFactory(lab, mImagesDir);
    auto cable = cableFactory.Create(zpm->GetPowerSource(),
                                                      panel->GetPowerSink());
    // Distribution to switch1
    cable = cableFactory.Create(panel->GetPowerSource(0),
            switch1->GetPowerSink(),
            30, 10);

    cable->AddClamp(Rack1X-80, -280, 0, 50);

    // Switch 1 to distribution 2
    cable = cableFactory.Create(switch1->GetPowerSource2(), panel2->GetPowerSink(),
            30, 30);

    // Switch 1 to light 3
    cable = cableFactory.Create(switch1->GetPowerSource1(), light3->GetPowerSink(),
            30, 30);

    cable->AddClamp(Rack1X-85, -250, 0.5, 50);
    cable->AddClamp(Rack1X-85, -180, 0.5, 70);

    // Distribution 2 source 1 to light 2
    cable = cableFactory.Create(panel2->GetPowerSource(0),
            light2->GetPowerSink(),
            30, 20);

    cable->AddClamp(Rack1X-85, -470, 0, 50);
    cable->AddClamp(Rack1X-85, -500, 0, 100);

    // Distribution 2 to light 1
    cable = cableFactory.Create(panel2->GetPowerSource(1),
            light1->GetPowerSink(),
            30, 20);

    cable->AddClamp(Rack1X-80, -470, 0, 50);
    cable->AddClamp(Rack1X-80, -550, 0, 100);

    // Distribution to switch2
    cable = cableFactory.Create(panel->GetPowerSource(1),
            switch2->GetPowerSink(),
            30, 10);
    cable->AddClamp(Rack1X+80, -280, 0, 50);

    // Switch 2 to Orbs
    cable = cableFactory.Create(switch2->GetPowerSource2(),
            orbs->GetPowerSink());

    // The bed
    auto bed = make_shared<Shape>(L"bed");
    bed->SetImage(mImagesDir + L"/bed.png");
    int wid = 400;
    bed->Rectangle(-wid/2, -10, wid);
    lab->AddComponent(bed);

    // Load the script
    lab->LoadScript(mResourcesDir + L"/scripts/laboratory1.xml");

    return lab;
}
