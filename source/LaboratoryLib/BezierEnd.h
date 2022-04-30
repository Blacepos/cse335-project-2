/**
 * @file BezierEnd.h
 * @author Joshua Austin
 *
 * Represents the end of a bezier curve
 */

#ifndef CANADIANEXPERIENCE_BEZIEREND_H
#define CANADIANEXPERIENCE_BEZIEREND_H

/**
 * Represents the end of a bezier curve
 */
class BezierEnd {
private:
    /// The position of the end
    wxPoint mPosition = wxPoint(0, 0);

    /// The rotation of the end
    double mRotation = 0.0;

    /// The speed of the end
    double mSpeed = 100.0;

    /// If the bezier end should follow another one, set this pointer
    BezierEnd* mFollowee = nullptr;

    /// The offset from the followee
    wxPoint mFolloweeOffset = wxPoint(0, 0);
public:
    /// Constructor
    BezierEnd() = default;

    /// Assignment operator/disabled
    void operator=(const BezierEnd&) = delete;

    wxPoint GetPosition();

    /**
     * Set the clamp position of this end
     * @param x The x position of the end
     * @param y The y position of the end
     */
    void SetPosition(int x, int y) { mPosition.x = x; mPosition.y = y; }

    /**
     * Set the clamp position of this end
     * @param position The position of the end
     */
    void SetPosition(wxPoint position) { mPosition = position; }

    /**
     * Get the rotation of the end
     * @return The rotation in whole rotations (1 rotation = 2*pi radians)
     */
    double GetRotation() const { return mRotation; }

    /**
     * Set the rotation of the end
     * @param rotation The rotation in whole rotations (1 rotation = 2*pi radians)
     */
    void SetRotation(double rotation) { mRotation = rotation; }

    /**
     * Get the speed of the end
     * @return The speed of the end
     */
    double GetSpeed() const { return mSpeed; }

    /**
     * Set the speed of the end
     * @param speed The speed of the end
     */
    void SetSpeed(double speed) { mSpeed = speed; }

    /**
     * Get the p1 point on the bezier end
     * @return point
     */
    wxPoint GetP1() { return GetPosition(); }

    wxPoint GetP2();

    wxPoint GetP3();

    /**
     * Get the p4 point on the bezier end
     * @return point
     */
    wxPoint GetP4() { return GetPosition(); }

    void SetFollowee(BezierEnd* end, wxPoint offset);
};

#endif //CANADIANEXPERIENCE_BEZIEREND_H
