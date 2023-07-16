#ifndef GEOGRAPHICCOORDSHANDLER_H
#define GEOGRAPHICCOORDSHANDLER_H

#include <QtMath>
#include <QPair>

class GeographicCoordsHandler
{
public:
    /* Параметры эллипсоида Красовского */
    /// Большая (экваториальная) полуось
    static constexpr qreal a = 6378245.0;
    /// Малая (полярная) полуось
    static constexpr qreal b = 6356863.019;
    /// Эксцентриситет
    static constexpr qreal e2 = ((a*a) - (b*b)) / (a*a);
    /// Приплюснутость
    static constexpr qreal n = (a - b) / (a + b);


    GeographicCoordsHandler();

    static QPair<qreal, qreal> fromDegreesToCartesian(qreal longitude_deg, qreal latitude_deg);

    static QPair<qreal, qreal> fromTilesToDegrees(int x, int y, int zoomLevel);

    static QPair<qreal, qreal> fromDegreesToTiles(qreal longitude_deg, qreal latitude_deg, int zoomLevel);

    static QPair<qreal, qreal> fromTilesToCartesian(int x, int y, int zoomLevel);
};

#endif // GEOGRAPHICCOORDSHANDLER_H
