/**
 * @file Component.h
 * @author Joshua Austin
 *
 * A laboratory component
 */

#ifndef CANADIANEXPERIENCE_COMPONENT_H
#define CANADIANEXPERIENCE_COMPONENT_H

/**
 * A laboratory component
 */
class Component {
private:
    /// The name of this component
    std::wstring mName;

    /// The current time in seconds measured by this object
    double mTime = 0.0;

protected:
    Component(std::wstring name);

public:
    /// Destructor
    virtual ~Component() = default;

    /// Default constructor/disabled
    Component() = delete;

    /// Copy constructor/disabled
    Component(const Component&) = delete;

    /// Assignment operator/disabled
    void operator=(const Component&) = delete;

    /**
     * Draw this component
     * @param graphics The context to draw on
     * @param position The position at which to draw the object
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) = 0;

    /**
     * Handle an event triggered by the animation
     * @param node An xml node
     */
    virtual void XmlEvent(wxXmlNode* node) {}

    /**
     * Get the current time stored by this object
     * @return The current time in seconds
     */
    double GetTime() const { return mTime; }

    /**
     * Set the current time stored by this object
     *
     * Override this to add custom behavior when the time changes
     * but be sure to upcall
     * @param time The current time in seconds
     */
    virtual void SetTime(double time) { mTime = time; }

    /**
     * Get the name of this component
     * @return
     */
    std::wstring GetName() const { return mName; }

    /**
     * Reset the state of this component
     */
    virtual void Reset() {}
};

#endif //CANADIANEXPERIENCE_COMPONENT_H
