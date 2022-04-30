/**
 * @file Winch.h
 * @author Joshua Austin
 *
 * An animated motion source component
 */

#ifndef CANADIANEXPERIENCE_WINCH_H
#define CANADIANEXPERIENCE_WINCH_H

#include "PolyComponent.h"
#include "Polygon.h"
#include "MotionSource.h"

/**
 * An animated motion source component
 */
class Winch : public PolyComponent {
private:
    /// Current rotation in whole rotations (1 rotation = 2*pi radians)
    double mRotation = 0.0;

    /// How fast the wheel should turn to reach the destination
    double mRotationsPerSecond = 0.0;

    /// The angle at which the wheel should stop
    double mDestination = 0.0;

    /// The background image
    cse335::Polygon mBackground;

    /// The motion source component of this winch
    MotionSource mMotionSource;
public:
    Winch(std::wstring imagesDir, std::wstring name);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint position) override;

    void XmlEvent(wxXmlNode* node) override;

    void RotateTo(double angle, double seconds);

    void SetTime(double time) override;

    /**
     * Get the current rotation
     * @return the current rotation in whole rotations (radians / (2*pi))
     */
    double GetRotation() const { return mRotation; }

    /**
     * Set the current rotation without animating
     * @param rotation Rotation in whole rotations (radians / (2*pi))
     */
    void SetRotation(double rotation) { mRotation = rotation; }

    /**
     * Get the motion source component of this winch
     * @return A pointer to the motion source
     */
    MotionSource* GetMotionSource() { return &mMotionSource; }

    void Reset() override;
};

#endif //CANADIANEXPERIENCE_WINCH_H
