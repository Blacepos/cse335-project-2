/**
 * @file BezierEnd.cpp
 * @author Joshua Austin
 */

#include "pch.h"
#include "BezierEnd.h"

/**
 * Set this bezier end to follow another bezier end
 * @param end The end to follow
 * @param offset The offset from the end
 */
void BezierEnd::SetFollowee(BezierEnd* end, wxPoint offset)
{
    mFollowee = end;
    mFolloweeOffset = offset;
}

/**
 * Get the clamp position of this end
 * @return The position of the end
 */
wxPoint BezierEnd::GetPosition()
{
    if (mFollowee != nullptr)
    {
        mPosition = mFollowee->GetPosition() + mFolloweeOffset;
    }
    return mPosition;
}

/**
 * Get the p2 point on the bezier end
 * @return point
 */
wxPoint BezierEnd::GetP2()
{
    return wxPoint(GetPosition().x + static_cast<int>(sin(mRotation * M_PI * 2) * mSpeed),
            GetPosition().y - static_cast<int>(cos(mRotation * M_PI * 2) * mSpeed));
}

/**
 * Get the p3 point on the bezier end
 * @return point
 */
wxPoint BezierEnd::GetP3()
{
    return wxPoint(GetPosition().x + static_cast<int>(sin((mRotation + 0.5) * M_PI * 2) * mSpeed),
            GetPosition().y - static_cast<int>(cos((mRotation + 0.5) * M_PI * 2) * mSpeed));
}
