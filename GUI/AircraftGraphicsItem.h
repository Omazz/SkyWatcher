#ifndef AIRCRAFTGRAPHICSITEM_H
#define AIRCRAFTGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class AircraftGraphicsItem : public QGraphicsItem
{
public:
    AircraftGraphicsItem();

    AircraftGraphicsItem(QString icao24);

    AircraftGraphicsItem(const AircraftGraphicsItem& other);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem* , QWidget* ) override;

    bool operator ==(const AircraftGraphicsItem& other);

    void operator =(const AircraftGraphicsItem& other);


    const QString &icao24() const;

private:
    QString m_icao24;
    QGraphicsTextItem m_textItemIcao24;
};

#endif // AIRCRAFTGRAPHICSITEM_H
