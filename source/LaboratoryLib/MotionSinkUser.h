/**
 * @file MotionSinkUser.h
 * @author Joshua Austin
 *
 * Interface for components which can be motion sinks
 *
 * This was originally called MotionSinkComponent in the UML, but I changed it because I thought it made more sense
 */

#ifndef CANADIANEXPERIENCE_MOTIONSINKUSER_H
#define CANADIANEXPERIENCE_MOTIONSINKUSER_H

/**
 * Interface for components which can be motion sinks
 * This was originally called MotionSinkComponent in the UML, but I changed it because I thought it made more sense
 */
class MotionSinkUser {
public:
    /// Constructor
    MotionSinkUser() = default;

    /// Copy constructor/disabled
    MotionSinkUser(const MotionSinkUser&) = delete;

    /// Assignment operator/disabled
    void operator=(const MotionSinkUser&) = delete;

    /**
     * Tell this motion sink user to respond to motion
     * @param amount How far to move
     * @param duration How much time to get to the destination
     */
    virtual void Drive(double amount, double duration) = 0;
};

#endif //CANADIANEXPERIENCE_MOTIONSINKUSER_H
