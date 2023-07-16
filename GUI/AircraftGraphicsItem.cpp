#include "AircraftGraphicsItem.h"

AircraftGraphicsItem::AircraftGraphicsItem() {

}

AircraftGraphicsItem::AircraftGraphicsItem(QString icao24) {
    m_icao24 = icao24;
}

AircraftGraphicsItem::AircraftGraphicsItem(const AircraftGraphicsItem& other) {
    m_icao24 = other.m_icao24;
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
    painter->setBrush(Qt::red);
    painter->drawPath(path);
}

bool AircraftGraphicsItem::operator ==(const AircraftGraphicsItem& other) {
    return m_icao24 == other.m_icao24;
}

void AircraftGraphicsItem::operator =(const AircraftGraphicsItem& other) {
    m_icao24 = other.m_icao24;
}

void AircraftGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (contains(event->pos())) {
        emit clickOnAircaft(m_icao24);
    }

    QGraphicsItem::mousePressEvent(event);
}
