#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QString>
#include <QVector>

const static quint8 NUMBER_PARAMETERS = 18;

enum OriginOfPosition {
    Adsb = 0,
    ASTERIX,
    MLAT,
    FLARM
};
enum AircraftCategory {
    NoInformationAtAll = 0,
    NoAdsbEmitterCategoryInformation,
    Light,
    Small,
    Large,
    HighVortexLarge,
    Heavy,
    HighPerfomance,
    Rotocraft,
    Glider,
    LighterThanAir,
    Parachutist,
    Ultralight,
    Reserved,
    UnmannedAerialVehicle,
    Space,
    EmergencyVehicle,
    ServiceVehicle,
    PointObstacle,
    ClusterObstacle,
    LineObstacle
};

struct Aircraft {
    QString icao24 = "";                 ///< Unique ICAO 24-bit address of the transponder in hex string representation.
    QString callsign = "";               ///< Callsign of the vehicle (8 chars). Can be null if no callsign has been received.
    bool callsign_isNull = true;
    QString origin_country = "";         ///< Country name inferred from the ICAO 24-bit address.
    int time_position;                  ///< Unix timestamp (seconds) for the last position update.
    bool time_position_isNull = true;
    int last_contact;                   ///< Unix timestamp (seconds) for the last update in general.
    float longitude;                    ///< WGS-84 longitude in decimal degrees. Can be null.
    bool longitude_isNull = true;
    float latitude;                     ///< WGS-84 latitude in decimal degrees. Can be null.
    bool latitude_isNull = true;
    float baro_altitude;                ///< Barometric altitude in meters. Can be null.
    bool baro_altitude_isNull = true;
    bool on_ground;                     ///< Boolean value which indicates if the position was retrieved from a surface position report.
    float velocity;                     ///< Velocity over ground in m/s. Can be null.
    bool velocity_isNull = true;
    float true_track;                   ///< True track in decimal degrees clockwise from north (north=0°). Can be null.
    bool true_track_isNull = true;
    float vertical_rate;                ///< Vertical rate in m/s.
    bool vertical_rate_isNull = true;
    QVector<int> sensors;           ///< IDs of the receivers which contributed to this state vector.
    float geo_altitude;                 ///< Geometric altitude in meters. Can be null.
    bool geo_altitude_isNull = true;
    QString squawk = "";                 ///< The transponder code aka Squawk. Can be null.
    bool squawk_isNull = true;
    bool spi;                           ///< Whether flight status indicates special purpose indicator.
    OriginOfPosition position_source;   ///< Origin of this state’s position.
    AircraftCategory category;          ///< Aircraft category.

    Aircraft() { }

    Aircraft(QString icao24, QString origin_country, int last_contact, bool on_ground,
             QVector<int> sensors, bool spi, OriginOfPosition position_source, AircraftCategory category) :
        icao24(icao24), origin_country(origin_country), last_contact(last_contact),
        on_ground(on_ground), sensors(sensors), spi(spi), position_source(position_source),
        category(category) { }
};

#endif // AIRCRAFT_H
