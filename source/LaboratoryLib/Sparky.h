/**
 * @file Sparky.h
 * @author Charles Owen
 *
 * Class to generate interesting lighting/spark effects
 */

#ifndef CANADIANEXPERIENCE_SPARKY_H
#define CANADIANEXPERIENCE_SPARKY_H

#include <wx/geometry.h>
#include <random>

namespace cse335 {
/**
 * Class to generate interesting lighting/spark effects
 */
    class Sparky final {
    private:
        /// Random number seed
        unsigned int mSeed;

        /// Random number generator
        std::mt19937 mRnd;

        /// Last time passed to SetTime
        double mLastTime = 0;

        /// Bolt intensity in range 0 to 1
        double mIntensity = 0.0;

        /// The spark color
        wxColour mColour = *wxRED;

        /**
         * A single line in the lightning bolt.
         */
        class Line {
        public:
            /// Point to draw from
            wxPoint2DDouble mA;

            /// Point to draw to
            wxPoint2DDouble mB;

            Line(wxPoint2DDouble a, wxPoint2DDouble b);

            void Draw(std::shared_ptr<wxGraphicsContext> graphics);
        };

        /// The current lighting bolt
        std::vector<Line> mBolt;

        std::vector<Line> CreateBolt(double length);

    public:
        Sparky();


        void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x1, double y1, double x2, double y2);

        /// Copy constructor (disabled)
        Sparky(const Sparky&) = delete;

        /// Assignment operator
        void operator=(const Sparky&) = delete;

        void Reset();

        void Update(double elapsed);

        void SetTime(double time);

        /**
         * Set the sparking intensity.
         * @param intensity Intensity range from 0 to 1. Larger values will also work.
         */
        void SetIntensity(double intensity) { mIntensity = intensity; }

        /**
         * Set the spark color (default is red)
         * @param colour Color to set
         */
        void SetColour(wxColour colour) { mColour = colour; }
    };
}

#endif //CANADIANEXPERIENCE_SPARKY_H
