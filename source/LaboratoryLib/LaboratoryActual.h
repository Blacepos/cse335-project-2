/**
 * @file LaboratoryActual.h
 * @author Joshua Austin
 *
 * The current fully-constructed laboratory
 */

#ifndef CANADIANEXPERIENCE_LABORATORYACTUAL_H
#define CANADIANEXPERIENCE_LABORATORYACTUAL_H

class Component;
class ZPM;

/**
 * The current fully-constructed laboratory
 */
class LaboratoryActual {
private:
    /// The animation script
    wxXmlDocument mXmlDoc;

    /// Which lab number this is
    int mLabNumber = 1;

    /// The current time
    double mTime = 0.0;

    /// A container for all of the components in the lab
    std::vector<std::shared_ptr<Component>> mComponents;

    /// An extra pointer to the lab's ZPM for sending power
    std::shared_ptr<ZPM> mZPM;

    /// A convenient storage format for en event
    struct Event
    {
        /// A pointer to the XmlNode object containing the rest of the event information
        wxXmlNode* mNode = nullptr;

        /// The name of the target component to receive the event
        std::wstring mTarget;

        /// The time at which the event should be fired
        double mTime = 0.0;
    };

    /// A container for every event loaded from the current xml document (assumes sorted order in the xml document)
    std::vector<std::unique_ptr<Event>> mEvents;

    /// The index of the next event to be consumed
    int mNextEvent = 0;

    void AddEvent(wxXmlNode* node);
public:
    /// Constructor
    explicit LaboratoryActual(int laboratoryNumber);

    /// Destructor
    virtual ~LaboratoryActual() = default;

    /// Copy constructor/disabled
    LaboratoryActual(const LaboratoryActual&) = delete;

    /// Assignment operator/disabled
    void operator=(const LaboratoryActual&) = delete;

    void DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position);

    void SetLaboratoryTime(double time);

    void LoadScript(std::wstring const& filename);

    /**
     * Get which lab this is
     * @return The lab number
     */
    int GetLaboratoryNumber() const { return mLabNumber; }

    void AddComponent(std::shared_ptr<Component> component);

    /**
     * Set the zpm pointer so the laboratory can distribute power
     * @param zpm zpm pointer
     */
    void SetZPM(std::shared_ptr<ZPM> zpm) { mZPM = zpm; }

    void Reset();
};

#endif //CANADIANEXPERIENCE_LABORATORYACTUAL_H
