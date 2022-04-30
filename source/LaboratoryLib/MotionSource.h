/**
 * @file MotionSource.h
 * @author Joshua Austin
 *
 * A component which handles sending motion to a sink
 */

#ifndef CANADIANEXPERIENCE_MOTIONSOURCE_H
#define CANADIANEXPERIENCE_MOTIONSOURCE_H

class MotionSinkUser;

/**
 * A component which handles sending motion to a sink
 */
class MotionSource {
private:
    /// A pointer to the component which can be driven
    MotionSinkUser* mMotionSinkUser = nullptr;

    /// How much to scale the input motion
    double mScale = 1.0;
public:
    MotionSource();

    /// Assignment operator/disabled
    void operator=(const MotionSource&) = delete;

    void Drive(double amount, double duration);

    /**
     * The MotionSinkUser associated with this source
     * @param sink The MotionSinkUser
     */
    void SetMotionSinkUser(MotionSinkUser* sink) { mMotionSinkUser = sink; }

    /**
     * Set the movement scale
     * @param scale The scale
     */
    void SetScale(double scale) { mScale = scale; }

    /**
     * Get the movement scale
     * @return The scale
     */
    double GetScale() const { return mScale; }
};

#endif //CANADIANEXPERIENCE_MOTIONSOURCE_H
