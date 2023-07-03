#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QtCore>

class MapView: public QGraphicsView {
Q_OBJECT

public:
    explicit MapView(QWidget* parent = nullptr, bool isMain = false);

    void setMain();

    void setIsField(bool newIsFied);

    bool isField() const;

    quint8 zoomLevel() const;
    void setZoomLevel(quint8 newZoomLevel);

protected:
    void wheelEvent(QWheelEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

    void mouseReleaseEvent(QMouseEvent* event) override;

signals:
    void clickOnField(quint8 zoomLevel, qreal x, qreal y);

    void changeMapToMain();

private:
    void zoom(qreal factor);

    QPointF m_previousMousePosition;
    quint8 m_zoomLevel;
    bool m_isMain = false;
    bool m_isField = false;
};

#endif // MAPVIEW_H
