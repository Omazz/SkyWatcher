#ifndef OPENSKYAPI_H
#define OPENSKYAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>


class OpenSkyAPI : public QObject
{
    Q_OBJECT
public:
    explicit OpenSkyAPI(QObject *parent = nullptr);

    void getStatesInField(qreal latitudeMin, qreal latitudeMax, qreal longitudeMin, qreal longitudeMax);

    ~OpenSkyAPI();

private slots:
    void readData();

    void finishReading();

signals:
    void updateData(QString data);

private:
    void clearValues();

    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
    QByteArray dataBuffer;
};

#endif // OPENSKYAPI_H
