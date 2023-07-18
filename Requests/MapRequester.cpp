#include "MapRequester.h"


MapRequester::MapRequester(QObject *parent)
    : QObject{parent}
{
    netManager = new QNetworkAccessManager(this);
    netReply = nullptr;
}

void MapRequester::clearValues() {
    dataBuffer.clear();
}

quint8 MapRequester::argY() const
{
    return m_argY;
}

quint8 MapRequester::argX() const
{
    return m_argX;
}


MapRequester::~MapRequester() {

}


void MapRequester::onClickOnField(quint8 zoomLevel, qreal x, qreal y) {
    clearValues();
    m_argX = x / 512. * qPow(2, zoomLevel);
    m_argY = y / 512. * qPow(2, zoomLevel);

    QNetworkRequest req{QUrl(QString("https://mt0.google.com/vt/lyrs=m&x=%1&y=%2&z=%3&hl=en").arg(m_argX).arg(m_argY).arg(zoomLevel))};

    netReply = netManager->get(req);
    connect(netReply,&QNetworkReply::readyRead,this,&MapRequester::readData);
    connect(netReply,&QNetworkReply::finished,this,&MapRequester::finishReading);
}

void MapRequester::readData()
{
    dataBuffer.append(netReply->readAll());
}

void MapRequester::finishReading()
{
    if(netReply->error() != QNetworkReply::NoError){
        qDebug() << "Error : " << netReply->errorString();
    }else{
        QImage image = QImage::fromData(dataBuffer, "PNG");

        if (image.isNull()) {
            qDebug() << "Error convert image";
            return;
        }

        emit updateMap(QPixmap::fromImage(image), m_argX, m_argY);
    }
}
