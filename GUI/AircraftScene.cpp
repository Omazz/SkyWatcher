#include "AircraftScene.h"

AircraftScene::AircraftScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

void AircraftScene::mousePressEvent(QGraphicsSceneMouseEvent* event)  {

    QGraphicsScene::mousePressEvent(event);

    QList<QGraphicsItem*> graphicsItems = items(event->scenePos());
    QVector<QString> aircrafts;
    aircrafts.reserve(graphicsItems.size());
    QMutableListIterator<QGraphicsItem*> iterator(graphicsItems);

    while(iterator.hasNext()) {
        QGraphicsItem* currentItem = iterator.next();
        AircraftGraphicsItem* currentAircraft = dynamic_cast<AircraftGraphicsItem*>(currentItem);
        if(currentAircraft != nullptr) {
            aircrafts.append(currentAircraft->icao24());
        }
    }

    if(!aircrafts.isEmpty()) {
        emit clickOnAircrafts(aircrafts);
    }
}
