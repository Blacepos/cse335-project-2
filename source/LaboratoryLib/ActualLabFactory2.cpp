/**
 * @file ActualLabFactory2.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "ActualLabFactory2.h"
#include "LaboratoryActual.h"
#include "ZPM.h"
#include "Rheostat.h"
#include "Cable.h"
#include "Light.h"
#include "CableFactory.h"
#include "VoltageMeter.h"
#include "EquipmentRack.h"
#include "Shape.h"
#include "Relay.h"
#include "Distribution.h"
#include "Switch.h"

using namespace std;

/**
 * Constructor
 * @param resourcesDir Path to program resources directory
 * @param imagesDir Path to the images directory
 */
ActualLabFactory2::ActualLabFactory2(std::wstring resourcesDir, std::wstring imagesDir)
        : mResourcesDir(resourcesDir), mImagesDir(imagesDir)
{
}

/**
 * Create a lab 2 instance
 * @return A shared pointer to a lab
 */
std::shared_ptr<LaboratoryActual> ActualLabFactory2::CreateActualLab()
{
    auto lab = make_shared<LaboratoryActual>(2);

    // create stuff
    auto background = make_shared<Shape>(L"Background");
    background->SetImage(mImagesDir + L"/building2.jpg");
    background->Rectangle(-600, 0);
    lab->AddComponent(background);

    auto zpm = make_shared<ZPM>(mImagesDir, L"ZPM");
    zpm->SetPosition(-550, -130);
    lab->AddComponent(zpm);
    lab->SetZPM(zpm);

    auto rheostat = make_shared<Rheostat>(mImagesDir, L"rheostat", 1000);
    rheostat->SetPosition(-400, -150);
    lab->AddComponent(rheostat);

    auto rack = std::make_shared<EquipmentRack>(mImagesDir, L"Rack 1");
    rack->SetPosition(200, -200);
    lab->AddComponent(rack);

    rack->AddBlankPanel(mImagesDir + L"/2u.png", 0);
    rack->AddBlankPanel(mImagesDir + L"/2u.png", 2);
    rack->AddBlankPanel(mImagesDir + L"/1u.png", 4);
    rack->AddBlankPanel(mImagesDir + L"/12u.png", 11);
    rack->AddBlankPanel(mImagesDir + L"/12u.png", 23);

    auto rack2 = std::make_shared<EquipmentRack>(mImagesDir, L"Rack 1");
    rack2->SetPosition(-200, -200);
    lab->AddComponent(rack2);

    rack2->AddBlankPanel(mImagesDir + L"/12u.png", 5);
    rack2->AddBlankPanel(mImagesDir + L"/12u.png", 17);
    rack2->AddBlankPanel(mImagesDir + L"/6u.png", 29);

    auto panel = make_shared<Distribution>(mImagesDir, L"panel", 1000);
    lab->AddComponent(panel);
    rack->SetPanelPosition(panel, 5);
    panel->AddSource(30);
    panel->AddSource(30);

    auto meter = make_shared<VoltageMeter>(mImagesDir, L"meter", 1000);
    lab->AddComponent(meter);
    rack2->SetPanelPosition(meter, 0);

    auto switch1 = make_shared<Switch>(mImagesDir, L"switch", 30, true);
    lab->AddComponent(switch1);
    rack2->SetPanelPosition(switch1, 5, 25);

    auto light = make_shared<Light>(mImagesDir, L"Light 2",
            L"/light2.png", L"/light2on.png", 100);
    auto lightsink = light->GetPowerSink();
    lightsink->SetRotation(0.12);
    lightsink->SetPosition(-35, -13);
    light->SetPosition(0, -550);
    lab->AddComponent(light);

    auto relay = make_shared<Relay>(mImagesDir, L"relay");
    rack->SetPanelPosition(relay, 23);
    lab->AddComponent(relay);

    CableFactory cableFactory(lab, mImagesDir);

    // zpm to rheostat
    auto cable = cableFactory.Create(zpm->GetPowerSource(), rheostat->GetPowerSink(), 50, 50);

    // rheostat to meter
    cable = cableFactory.Create(rheostat->GetPowerSource(), meter->GetPowerSink(), 50, 50);

    // meter to panel
    cable = cableFactory.Create(meter->GetPowerSource(), panel->GetPowerSink(), 100, 50);

    // panel to switch
    cable = cableFactory.Create(panel->GetPowerSource(0), switch1->GetPowerSink(), 40, 30);
    cable->AddClamp(0, -280, 0.75, 80);

    // switch to relay coil
    cable = cableFactory.Create(switch1->GetPowerSource2(), relay->GetPowerSinkCoil());

    // panel to relay main
    cable = cableFactory.Create(panel->GetPowerSource(1), relay->GetPowerSinkRelay(), 20);

    // relay to light
    cable = cableFactory.Create(relay->GetPowerSource2(), light->GetPowerSink());

    lab->LoadScript(mResourcesDir + L"/scripts/laboratory2.xml");

    return lab;
}