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

    AircraftGraphicsItem(QString icao24, QColor color, bool isSelectedUser);

    AircraftGraphicsItem(const AircraftGraphicsItem& other);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem* , QWidget* ) override;

    bool operator ==(const AircraftGraphicsItem& other);

    void operator =(const AircraftGraphicsItem& other);


    const QString &icao24() const;

    const QColor &color() const;

    void setColor(const QColor &newColor);



    bool isSelectedUser() const;
    void setIsSelectedUser(bool newIsSelectedUser);

private:
    QString m_icao24;
    QColor m_color;
    bool m_isSelectedUser = false;
};

#endif // AIRCRAFTGRAPHICSITEM_H
