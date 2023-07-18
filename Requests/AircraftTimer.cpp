#include "AircraftTimer.h"

AircraftTimer::AircraftTimer(QObject *parent)
    : QTimer{parent}
{

}

quint8 AircraftTimer::zoomLevel() const
{
    return m_zoomLevel;
}

void AircraftTimer::setZoomLevel(quint8 newZoomLevel)
{
    m_zoomLevel = newZoomLevel;
}

qreal AircraftTimer::x() const
{
    return m_x;
}

void AircraftTimer::setX(qreal newX)
{
    m_x = newX;
}

qreal AircraftTimer::y() const
{
    return m_y;
}

void AircraftTimer::setY(qreal newY)
{
    m_y = newY;
}
