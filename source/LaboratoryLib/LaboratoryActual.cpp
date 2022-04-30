/**
 * @file LaboratoryActual.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "LaboratoryActual.h"
#include "Component.h"
#include "ZPM.h"

/**
 * Constructor
 * @param laboratoryNumber Which lab this is
 */
LaboratoryActual::LaboratoryActual(int laboratoryNumber) : mLabNumber(laboratoryNumber)
{

}

/**
 * Draw the lab
 * @param graphics The context to draw to
 * @param position Where to draw the laboratory
 */
void LaboratoryActual::DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position)
{
    for (auto const& component : mComponents)
    {
        component->Draw(graphics, position);
    }
}

/**
 * Set the time of the laboratory
 * @param time The frame
 */
void LaboratoryActual::SetLaboratoryTime(double time)
{
    mTime = time;

    // Update the power throughout the laboratory
    if (mZPM != nullptr)
    {
        mZPM->SendPower();
    }

    //
    // Send any events that become active to the components
    //
    while(mNextEvent < mEvents.size() && mEvents[mNextEvent]->mTime <= time)
    {
        // Process this event
        auto& event = mEvents[mNextEvent];

        for(auto const& component : mComponents)
        {
            if(component->GetName() == event->mTarget)
            {
                component->XmlEvent(event->mNode);
            }
        }

        mNextEvent++;
    }

    // Set the time for each component
    for (auto const& component : mComponents)
    {
        component->SetTime(time);
    }
}

/**
 * Load a script from an xml file
 * @param filename The file name
 */
void LaboratoryActual::LoadScript(const std::wstring& filename)
{
    if(!mXmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load animation xml script");
    }

    auto child = mXmlDoc.GetRoot()->GetChildren();

    while (child != nullptr)
    {
        AddEvent(child);
        child = child->GetNext();
    }
}

/**
 * Add a component to the laboratory
 * @param component A pointer to the component
 */
void LaboratoryActual::AddComponent(std::shared_ptr<Component> component)
{
    // This is just a one-way association
    mComponents.push_back(component);
}

/**
 * Add an event from an xml node.
 *
 * Convenience function for setting the values of each Event.
 * @param node The xml node to add
 */
void LaboratoryActual::AddEvent(wxXmlNode* node)
{
    auto event = std::make_unique<Event>();
    event->mNode = node;
    event->mTarget = node->GetAttribute(L"target");
    node->GetAttribute(L"time").ToDouble(&event->mTime);

    mEvents.push_back(std::move(event));
}

/**
 * Reset the lab and the components to their initial state
 */
void LaboratoryActual::Reset()
{
    mNextEvent = 0;
    // Set the time for each component
    for (auto const& component : mComponents)
    {
        component->Reset();
    }
}
