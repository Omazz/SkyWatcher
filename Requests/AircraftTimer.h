#ifndef AIRCRAFTTIMER_H
#define AIRCRAFTTIMER_H

#include <QTimer>

class AircraftTimer : public QTimer
{
    Q_OBJECT
public:
    explicit AircraftTimer(QObject *parent = nullptr);

    quint8 zoomLevel() const;
    void setZoomLevel(quint8 newZoomLevel);

    qreal x() const;
    void setX(qreal newX);

    qreal y() const;
    void setY(qreal newY);

private:
    quint8 m_zoomLevel;
    qreal m_x;
    qreal m_y;
};

#endif // AIRCRAFTTIMER_H
