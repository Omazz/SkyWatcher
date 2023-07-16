#ifndef AIRCRAFTREQUESTER_H
#define AIRCRAFTREQUESTER_H


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
#include "PriFiles/GeographicCoordsHandler/GeographicCoordsHandler.h"
#include "Aircraft.h"

class AircraftRequester : public QObject
{
    Q_OBJECT
public:
    explicit AircraftRequester(QObject *parent = nullptr);

    ~AircraftRequester();

public slots:
    void onClickOnField(quint8 zoomLevel, qreal x, qreal y);

private slots:
    void readData();

    void finishReading();

signals:
    void updateAircrafts(QVector<Aircraft> aircrafts);

private:
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QByteArray dataBuffer;
};

#endif // AIRCRAFTREQUESTER_H
