/**
 * @file LaboratoryStandin.h
 *
 * @author Charles Owen
 *
 * This class is a stand-in class that will allow you to
 * develop the laboratory adapter class first if you so choose. It
 * provides some graphics that represent where the laboratory
 * will be created and information about the status of the
 * laboratory.
 *
 * You are not allowed to change this class in any way!
 */

#pragma once

#include <vector>
#include <memory>
#include <string>


/**
 * This class is a stand-in class that will allow you to
 * develop the laboratory adapter class first if you so choose. It
 * provides some graphics that represent where the laboratory
 * will be created and information about the status of the
 * laboratory.
 *
 * **You are not allowed to change this class in any way!**
 */
class LaboratoryStandin
{

private:
    void CenteredString(std::shared_ptr<wxGraphicsContext> graphics, const std::wstring &str, int x, int y, int dy);

    int mX = 0;     ///< Laboratory X location
    int mY = 0;     ///< Laboratory Y location
    int mFrame = 0; ///< Current frame
    int mLaboratory = 1;  ///< Laboratory number

public:
    LaboratoryStandin();

    /**
    * Set the position for the root of the laboratory
    * @param location X,Y location in pixels
    */
    void SetLocation(wxPoint location) { mX = location.x; mY = location.y; }

    /**
     * Get the root position of the laboratory
     * @return location x,y in pixels as a point
     */
    wxPoint GetLocation() {return wxPoint(mX, mY);}

    void DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics);

    /**
    * Set the current laboratory animation frame
    * @param frame Frame number
    */
    void SetLaboratoryFrame(int frame) { mFrame = frame; }

    /**
    * Set the laboratory number
    * @param laboratory An integer number. Each integer makes a different laboratory
    */
    void SetLaboratory(int laboratory) { mLaboratory = laboratory; }

    /**
    * Get the current laboratory number
    * @return Laboratory number
    */
    virtual int GetLaboratory() { return mLaboratory; }
};

