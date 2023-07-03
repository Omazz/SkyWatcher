#include "MapView.h"

MapView::MapView(QWidget* parent, bool isMain) : QGraphicsView(parent), m_isMain(isMain) {
    setTransformationAnchor(QGraphicsView::NoAnchor);
}


void MapView::wheelEvent(QWheelEvent* event) {

    if(!m_isMain) {
        return;
    }

    qreal zoomFactor = qPow(1.0015, event->angleDelta().y());
    zoom(zoomFactor);

    QPointF mousePos = mapToScene(mapFromGlobal(event->globalPos()));
    QPointF centerPos = mapToScene(viewport()->rect().center());
    QPointF delta = (mousePos - centerPos) / 4;

    translate(-delta.x(), -delta.y());
}

void MapView::keyPressEvent(QKeyEvent* event) {
    QGraphicsView::keyPressEvent(event);

    if(!m_isMain) {
        return;
    }

    if(event->key() == Qt::Key_Space) {
        emit changeMapToMain();
    }
}

void MapView::zoom(qreal factor) {
    QPointF oldPos = mapToScene(viewport()->rect().center());

    if (transform().m22() * factor >= 0.99 && transform().m22() * factor <= 7.5) {
        scale(factor, factor);
    }

    QPointF newPos = mapToScene(viewport()->rect().center());

    QPointF delta = newPos - oldPos;
    translate(delta.x(), delta.y());
}

quint8 MapView::zoomLevel() const
{
    return m_zoomLevel;
}

void MapView::setZoomLevel(quint8 newZoomLevel)
{
    m_zoomLevel = newZoomLevel;
}

bool MapView::isField() const
{
    return m_isField;
}

void MapView::setIsField(bool newIsFied)
{
    m_isField = newIsFied;
}

void MapView::setMain()
{
    m_isMain = true;
}

void MapView::mouseReleaseEvent(QMouseEvent* event) {
    QGraphicsView::mouseReleaseEvent(event);

    if(!m_isMain || m_isField) {
        return;
    }

    QPointF clickPos = mapToScene(event->pos());

    emit clickOnField(m_zoomLevel, clickPos.x(), clickPos.y());
    //qDebug() << clickPos.x() << clickPos.y();

}
