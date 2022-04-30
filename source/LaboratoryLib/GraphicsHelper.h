/**
 * @file GraphicsHelper.h
 * @author Charles Owen
 *
 * Helper class with simple graphics context functions.
 */

#ifndef CANADIANEXPERIENCE_GRAPHICSHELPER_H
#define CANADIANEXPERIENCE_GRAPHICSHELPER_H

namespace cse335 {

/**
 * Helper class with simple graphics context functions.
 */
    class GraphicsHelper {
    public:
        static void DrawCrosshair(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, int size = 10,
                wxColour color = *wxRED);

        static wxPoint2DDouble ToVector(double angle, double length);

        static wxPoint ToIntVector(double angle, double length);
    };

}

#endif //CANADIANEXPERIENCE_GRAPHICSHELPER_H
