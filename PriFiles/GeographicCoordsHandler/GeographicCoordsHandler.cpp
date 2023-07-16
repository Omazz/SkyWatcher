#include "GeographicCoordsHandler.h"

GeographicCoordsHandler::GeographicCoordsHandler()
{

}

QPair<qreal, qreal> GeographicCoordsHandler::fromDegreesToCartesian(qreal longitude_deg, qreal latitude_deg) {

    /// Номер зоны Гаусса-Крюгера
    int zone = (longitude_deg / 6.0) + 1;

    /* Параметры зоны Гаусса-Крюгера */
    /// Масштабный коэффициент
    qreal F = 1.0;
    /// Начальная параллель (в радианах)
    qreal latitude_0 = 0.0;
    /// Центральный меридиан (в радианах)
    qreal longitude_0 = qDegreesToRadians((qreal)(zone * 6 - 3));
    /// Условное северное смещение для начальной параллели
    qreal N0 = 0.0;
    /// Условное восточное смещение для центрального меридиана
    qreal E0 = (zone * 1e6) + 500000.0;

    /* Перевод широты и долготы из градусов в радианы */
    qreal longitude_rad = qDegreesToRadians(longitude_deg);
    qreal latitude_rad = qDegreesToRadians(latitude_deg);

    /* Вычисление переменных для преобразования */
    qreal sinLat = qSin(latitude_rad);
    qreal cosLat = qCos(latitude_rad);
    qreal tanLat = qTan(latitude_rad);

    qreal v = a * F * qPow(1.0 - (e2* qPow(sinLat, 2)),-0.5);
    qreal p = a * F * (1.0 - e2) * qPow(1.0 - (e2 * qPow(sinLat, 2)),-1.5);
    qreal n2 = (v / p) - 1.0;
    qreal M1 = (1 + n + (5.0 / 4.0 * qPow(n, 2)) + (5.0/4.0 * qPow(n, 3))) * (latitude_rad - latitude_0);
    qreal M2 = ((3*n)+(3* qPow(n,2)) +(21.0/8.0* qPow(n,3))) * qSin(latitude_rad - latitude_0) * qCos(latitude_rad + latitude_0);
    qreal M3 = ((15.0/8.0 * qPow(n,2)) +(15.0/8.0* qPow(n,3)))*qSin(2.0 * (latitude_rad - latitude_0))*qCos(2.0 * (latitude_rad + latitude_0));
    qreal M4 = 35.0/24.0* qPow(n,3) *qSin(3.0 * (latitude_rad - latitude_0)) * qCos(3.0 * (latitude_rad + latitude_0));
    qreal M = b*F*(M1-M2+M3-M4);
    qreal I = M+N0;
    qreal II = v / 2.0 * sinLat * cosLat;
    qreal III = v / 24.0 * sinLat * qPow(cosLat,3) * (5.0 - qPow(tanLat,2) + (9*n2));
    qreal IIIA = v / 720.0 * sinLat * qPow(cosLat,5) * (61.0 - (58.0 * qPow(tanLat,2)) + qPow(tanLat,4));
    qreal IV = v * cosLat;
    qreal V = v / 6.0 * qPow(cosLat,3) * ((v / p)-qPow(tanLat,2));
    qreal VI = v / 120.0 * qPow(cosLat,5) * (5.0 - (18.0*qPow(tanLat,2))+qPow(tanLat,4)+(14*n2)-(58.0*qPow(tanLat,2)*n2));

    /* Вычисление северного и восточного смещения (в метрах) */
    qreal N = I+(II* qPow(longitude_rad-longitude_0,2))+(III* qPow(longitude_rad-longitude_0,4))+(IIIA* qPow(longitude_rad-longitude_0,6));
    qreal E = E0+(IV*(longitude_rad-longitude_0))+(V* qPow(longitude_rad-longitude_0,3))+(VI* qPow(longitude_rad-longitude_0,5));


    return QPair<qreal, qreal>(N, E);
}

QPair<qreal, qreal> GeographicCoordsHandler::fromTilesToDegrees(int x, int y, int zoomLevel) ///< return (longitude, latitude)
{
    qreal longitude = x / (double)(1 << zoomLevel) * 360.0 - 180;
    qreal latitude = qRadiansToDegrees(qAtan(sinh(M_PI - (y / qPow(2, zoomLevel) * 2. * M_PI))));

    return QPair<qreal, qreal>(longitude, latitude);
}

QPair<qreal, qreal> GeographicCoordsHandler::fromDegreesToTiles(qreal longitude_deg, qreal latitude_deg, int zoomLevel) ///< return (x, y)
{
    qreal x = ((longitude_deg + 180.0) / 360.0 * (1 << zoomLevel));
    qreal y = ((1.0 - asinh(tan(qDegreesToRadians(latitude_deg))) / M_PI) / 2.0 * (1 << zoomLevel));

    return QPair<qreal, qreal>(x, y);
}

QPair<qreal, qreal> GeographicCoordsHandler::fromTilesToCartesian(int x, int y, int zoomLevel) {
    QPair<qreal, qreal> res = fromTilesToDegrees(x, y, zoomLevel);
    return fromDegreesToCartesian(res.first, res.second);
}
