#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QObject>
#include <QGraphicsView>

class MapView: public QGraphicsView {
Q_OBJECT

public:
    explicit MapView(QWidget* parent = nullptr);
};

#endif // MAPVIEW_H
