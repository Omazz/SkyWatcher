#include "AircraftRequester.h"

AircraftRequester::AircraftRequester(QObject *parent)
    : QObject{parent}
{
    netManager = new QNetworkAccessManager(this);
    netReply = nullptr;
}

AircraftRequester::~AircraftRequester() {

}

void AircraftRequester::onGetAircraftsInField() {
    QObject* object = sender();
    if(object) {
        AircraftTimer* timer = dynamic_cast<AircraftTimer*>(object);
        if(timer) {
            int argX = timer->x() / 512 * qPow(2, timer->zoomLevel());
            int argY = timer->y() / 512 * qPow(2, timer->zoomLevel());

            QPair<qreal, qreal> firstCoord = GeographicCoordsHandler::fromTilesToDegrees(argX, argY, timer->zoomLevel());
            QPair<qreal, qreal> secondCoord = GeographicCoordsHandler::fromTilesToDegrees(argX + 1, argY + 1, timer->zoomLevel());
            qreal longitudeMin = firstCoord.first;
            qreal latitudeMax = firstCoord.second;
            qreal longitudeMax = secondCoord.first;
            qreal latitudeMin = secondCoord.second;

            QNetworkRequest req{QUrl(QString("https://opensky-network.org/api/states/all?lamin=%1&lomin=%2&lamax=%3&lomax=%4")
                                     .arg(latitudeMin).arg(longitudeMin).arg(latitudeMax).arg(longitudeMax))};

            netReply = netManager->get(req);

            connect(netReply,&QNetworkReply::readyRead,this,&AircraftRequester::readData);
            connect(netReply,&QNetworkReply::finished,this,&AircraftRequester::finishReading);
        }
    }
}

void AircraftRequester::readData()
{
    dataBuffer.append(netReply->readAll());
}

void AircraftRequester::finishReading()
{
    if(netReply->error() != QNetworkReply::NoError){
            qDebug() << "Error : " << netReply->errorString();
    }else{

        //CONVERT THE DATA FROM A JSON DOC TO A JSON OBJECT
        QJsonObject jsonObject = QJsonDocument::fromJson(dataBuffer).object();

        QJsonArray jsonArray = jsonObject.value("states").toArray();

        QVector<Aircraft> aircrafts;
        aircrafts.reserve(jsonArray.size());

        for(int i = 0; i < jsonArray.size(); ++i) {
            QJsonArray currentAircraft = jsonArray.at(i).toArray();
            Aircraft aircraft;
            aircraft.icao24 = currentAircraft.at(0).toString();
            aircraft.callsign_isNull = currentAircraft.at(1).isNull();
            if(!aircraft.callsign_isNull) {
                aircraft.callsign = currentAircraft.at(1).toString();
            }
            aircraft.origin_country = currentAircraft.at(2).toString();
            aircraft.time_position_isNull = currentAircraft.at(3).isNull();
            if(!aircraft.time_position_isNull) {
                aircraft.time_position = currentAircraft.at(3).toInt();
            }
            aircraft.last_contact = currentAircraft.at(4).toInt();
            aircraft.longitude_isNull = currentAircraft.at(5).isNull();
            if(!aircraft.longitude_isNull) {
                aircraft.longitude = currentAircraft.at(5).toDouble();
            }
            aircraft.latitude_isNull = currentAircraft.at(6).isNull();
            if(!aircraft.latitude_isNull) {
                aircraft.latitude = currentAircraft.at(6).toDouble();
            }
            aircraft.baro_altitude_isNull = currentAircraft.at(7).isNull();
            if(!aircraft.baro_altitude_isNull) {
                aircraft.baro_altitude = currentAircraft.at(7).toDouble();
            }
            aircraft.on_ground = currentAircraft.at(8).toBool();
            aircraft.velocity_isNull = currentAircraft.at(9).isNull();
            if(!aircraft.velocity_isNull) {
                aircraft.velocity = currentAircraft.at(9).toDouble();
            }
            aircraft.true_track_isNull = currentAircraft.at(10).isNull();
            if(!aircraft.true_track_isNull) {
                aircraft.true_track = currentAircraft.at(10).toDouble();
            }
            aircraft.vertical_rate_isNull = currentAircraft.at(11).isNull();
            if(!aircraft.vertical_rate_isNull) {
                aircraft.vertical_rate = currentAircraft.at(11).toDouble();
            }
            if(!currentAircraft.at(12).isNull()) {
                QJsonArray array = currentAircraft.at(12).toArray();
                aircraft.sensors.reserve(array.size());
                for(int i = 0; i < array.size(); ++i) {
                    aircraft.sensors.append(array.at(i).toInt());
                }
            }
            aircraft.geo_altitude_isNull = currentAircraft.at(13).isNull();
            if(!aircraft.geo_altitude_isNull) {
                aircraft.geo_altitude = currentAircraft.at(13).toDouble();
            }
            aircraft.squawk_isNull = currentAircraft.at(14).isNull();
            if(!aircraft.squawk_isNull) {
                aircraft.squawk = currentAircraft.at(14).toString();
            }
            aircraft.spi = currentAircraft.at(15).toBool();
            aircraft.position_source = static_cast<OriginOfPosition>(currentAircraft.at(16).toInt());
            aircraft.category = static_cast<AircraftCategory>(currentAircraft.at(17).toInt());

            aircrafts.append(aircraft);
        }

        emit updateAircrafts(aircrafts);

        dataBuffer.clear();
    }
}
