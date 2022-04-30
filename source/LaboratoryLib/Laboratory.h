/**
 * @file Laboratory.h
 * @author Charles Owen
 *
 * Class that represents a laboratory.
 *
 * You are not allowed to change this class in any way!
 */

#ifndef CANADIANEXPERIENCE_LABORATORY_H
#define CANADIANEXPERIENCE_LABORATORY_H

class LaboratoryStandin;

/**
 * Class that represents a laboratory.
 *
 * This uses a standin class to provide a way to develop
 * the adapter class first if you so choose.
 *
 * You are not allowed to change this class in any way!
 */
class Laboratory {
private:
    /**
     * A stand-in laboratory class.
     *
     * This draws simple stand-in graphics
     * so you can see where the laboratory will be and what its state
     * is. This makes it easy to develop code that uses the
     * laboratory before you have the laboratory working.
     *
     * And no, you may not change this to point to your
     * laboratory implementation!
     */
    std::shared_ptr<LaboratoryStandin> mStandin;

public:
    /// Constructor
    Laboratory();

    /// Destructor
    virtual ~Laboratory() = default;

    /// Copy constructor/disabled
    Laboratory(const Laboratory&) = delete;

    /// Assignment operator/disabled
    void operator=(const Laboratory&) = delete;

    /**
    * Set the position for the root of the laboratory
    * @param location The x,y location to place the laboratory
    */
    virtual void SetLocation(wxPoint location);

    /**
     * Get the location of the laboratory
     * @return Location x,y in pixels as a point
     */
    virtual wxPoint GetLocation();

    /**
    * Draw the laboratory at the currently specified location
    * @param graphics Graphics object to render to
    */
    virtual void DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics);

    /**
    * Set the current laboratory animation frame
    * @param frame Frame number
    */
    virtual void SetLaboratoryFrame(int frame);

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    virtual void SetFrameRate(double rate);

    /**
    * Set the laboratory number
    * @param laboratory An integer number. Each number makes a different laboratory
    */
    virtual void SetLaboratoryNumber(int laboratory);

    /**
     * Get the current laboratory number
     * @return Laboratory number integer
     */
    virtual int GetLaboratoryNumber();

    /**
     * Get the current laboratory time.
     * @return Laboratory time in seconds
     */
    virtual double GetLaboratoryTime();
};


#endif //CANADIANEXPERIENCE_LABORATORY_H
