#ifndef GEOCALCULATOR_H
#define GEOCALCULATOR_H

#include <QtMath>
#include <QPair>


class GeoCalculator {
public:
    static QPair<qreal, qreal> fromTilesToDegrees(int x, int y, int zoomLevel) ///< return (longitude, latitude)
    {
        qreal longitude = x / (double)(1 << zoomLevel) * 360.0 - 180;
        qreal latitude = qRadiansToDegrees(qAtan(sinh(M_PI - (y / qPow(2, zoomLevel) * 2. * M_PI))));

        return QPair<qreal, qreal>(longitude, latitude);
    }

    static QPair<int, int> fromDegreesToTiles(qreal longitude_deg, qreal latitude_deg, int zoomLevel) ///< return (x, y)
    {
        int x = floor((longitude_deg + 180.0) / 360.0 * (1 << zoomLevel));
        int y = floor((1.0 - asinh(tan(qDegreesToRadians(latitude_deg))) / M_PI) / 2.0 * (1 << zoomLevel));

        return QPair<int, int>(x, y);
    }
};

#endif // GEOCALCULATOR_H
