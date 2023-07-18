#ifndef MAPREQUESTER_H
#define MAPREQUESTER_H

#include <QObject>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QtCore>

class MapRequester : public QObject
{
    Q_OBJECT
public:
    explicit MapRequester(QObject *parent = nullptr);

    ~MapRequester();

    quint8 argX() const;

    quint8 argY() const;

public slots:
    void onClickOnField(quint8 zoomLevel, qreal x, qreal y);

private slots:
    void readData();

    void finishReading();

signals:
    void updateMap(QPixmap map, quint8 x, quint8 y);

private:
    void clearValues();

    quint8 m_argX, m_argY;

    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QByteArray dataBuffer;
};

#endif // MAPREQUESTER_H
