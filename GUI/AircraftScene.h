#ifndef AIRCRAFTSCENE_H
#define AIRCRAFTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QGraphicsItem>
#include "AircraftGraphicsItem.h"

class AircraftScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AircraftScene(QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void clickOnAircrafts(QVector<QString> aircrafts);
};

#endif // AIRCRAFTSCENE_H
