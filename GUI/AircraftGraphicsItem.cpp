#include "AircraftGraphicsItem.h"

AircraftGraphicsItem::AircraftGraphicsItem() {

}

AircraftGraphicsItem::AircraftGraphicsItem(QString icao24, QColor color, bool isSelectedUser) {
    m_icao24 = icao24;
    m_color = color;
    m_isSelectedUser = isSelectedUser;
}

AircraftGraphicsItem::AircraftGraphicsItem(const AircraftGraphicsItem& other) {
    m_icao24 = other.m_icao24;
    m_color = other.m_color;
    m_isSelectedUser = other.m_isSelectedUser;
}

QRectF AircraftGraphicsItem::boundingRect() const {
    return QRectF(-5, -6, 10, 12);
}

void AircraftGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    QPainterPath path;

    path.moveTo(0, -5);
    path.lineTo(1, -3);
    path.lineTo(1, -1);
    path.lineTo(5, 1);
    path.lineTo(1, 1);
    path.lineTo(1, 4);
    path.lineTo(2.5, 6);
    path.lineTo(1.5, 6);

    path.lineTo(0, 5);

    path.lineTo(-1.5, 6);
    path.lineTo(-2.5, 6);
    path.lineTo(-1, 4);
    path.lineTo(-1, 1);
    path.lineTo(-5, 1);
    path.lineTo(-1, -1);
    path.lineTo(-1, -3);
    path.lineTo(0, -5);

    path.closeSubpath();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_color);
    painter->drawPath(path);
}

bool AircraftGraphicsItem::operator ==(const AircraftGraphicsItem& other) {
    return (m_icao24 == other.m_icao24);
}

void AircraftGraphicsItem::operator =(const AircraftGraphicsItem& other) {
    m_icao24 = other.m_icao24;
    m_color = other.m_color;
    m_isSelectedUser = other.m_isSelectedUser;
}

const QString &AircraftGraphicsItem::icao24() const
{
    return m_icao24;
}

const QColor &AircraftGraphicsItem::color() const
{
    return m_color;
}

void AircraftGraphicsItem::setColor(const QColor &newColor)
{
    m_color = newColor;
}

bool AircraftGraphicsItem::isSelectedUser() const
{
    return m_isSelectedUser;
}

void AircraftGraphicsItem::setIsSelectedUser(bool newIsSelectedUser)
{
    m_isSelectedUser = newIsSelectedUser;
}


