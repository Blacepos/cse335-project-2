/**
 * @file MotionSource.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "MotionSource.h"
#include "MotionSinkUser.h"

/// Constructor
MotionSource::MotionSource()
{
}

/**
 * Sends motion to a MotionSinkUser
 * @param amount The destination
 * @param duration The amount of time to reach the destination
 */
void MotionSource::Drive(double amount, double duration)
{
    if (mMotionSinkUser != nullptr)
    {
        mMotionSinkUser->Drive(amount * mScale, duration);
    }
}
