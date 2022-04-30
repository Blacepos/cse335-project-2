/**
 * @file PowerSinkUser.h
 * @author Joshua Austin
 *
 * Interface for overriding PowerSink behavior for those that have it.
 *
 * This was originally called PowerSinkComponent in the UML, but I changed it because I thought it made more sense
 */

#ifndef CANADIANEXPERIENCE_POWERSINKUSER_H
#define CANADIANEXPERIENCE_POWERSINKUSER_H

/**
 * Interface for overriding PowerSink behavior for those that have it.
 *
 * This was originally called PowerSinkComponent in the UML, but I changed it because I thought it made more sense
 */
class PowerSinkUser {
public:
    /// Constructor
    PowerSinkUser() = default;

    /// Copy constructor/disabled
    PowerSinkUser(const PowerSinkUser&) = delete;

    /// Assignment operator/disabled
    void operator=(const PowerSinkUser&) = delete;

    /**
     * Send power to this lab component
     * @param voltage How much power to send
     * @return The current in response
     */
    virtual double Power(double voltage) = 0;
};

#endif //CANADIANEXPERIENCE_POWERSINKUSER_H
