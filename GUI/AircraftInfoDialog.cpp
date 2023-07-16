#include "AircraftInfoDialog.h"
#include "ui_AircraftInfoDialog.h"

AircraftInfoDialog::AircraftInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AircraftInfoDialog)
{
    ui->setupUi(this);
}


void AircraftInfoDialog::setAircraftInfo(const Aircraft& aircraft) {
    ui->TW_aircraftInfo->setRowCount(NUMBER_PARAMETERS);
    ui->TW_aircraftInfo->setColumnCount(1);
    ui->TW_aircraftInfo->setHorizontalHeaderItem(0, new QTableWidgetItem("Information"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(0, new QTableWidgetItem("ICAO-24"));
    ui->TW_aircraftInfo->setItem(0, 0, new QTableWidgetItem(aircraft.icao24));

    ui->TW_aircraftInfo->setVerticalHeaderItem(1, new QTableWidgetItem("Callsign"));
    if(aircraft.callsign_isNull) {
        ui->TW_aircraftInfo->setItem(1, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(1, 0, new QTableWidgetItem(aircraft.callsign));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(2, new QTableWidgetItem("Country"));
    ui->TW_aircraftInfo->setItem(2, 0, new QTableWidgetItem(aircraft.origin_country));

    ui->TW_aircraftInfo->setVerticalHeaderItem(3, new QTableWidgetItem("Time position, s"));
    if(aircraft.time_position_isNull) {
        ui->TW_aircraftInfo->setItem(3, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(3, 0, new QTableWidgetItem(QString::number(aircraft.time_position)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(4, new QTableWidgetItem("Last contact, s"));
    ui->TW_aircraftInfo->setItem(4, 0, new QTableWidgetItem(QString::number(aircraft.last_contact)));

    ui->TW_aircraftInfo->setVerticalHeaderItem(5, new QTableWidgetItem("Longitude, °"));
    if(aircraft.longitude_isNull) {
        ui->TW_aircraftInfo->setItem(5, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(5, 0, new QTableWidgetItem(QString::number(aircraft.longitude)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(6, new QTableWidgetItem("Latitude, °"));
    if(aircraft.latitude_isNull) {
        ui->TW_aircraftInfo->setItem(6, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(6, 0, new QTableWidgetItem(QString::number(aircraft.latitude)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(7, new QTableWidgetItem("Barometric altitude, m"));
    if(aircraft.baro_altitude_isNull) {
        ui->TW_aircraftInfo->setItem(7, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(7, 0, new QTableWidgetItem(QString::number(aircraft.baro_altitude)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(8, new QTableWidgetItem("On ground"));
    ui->TW_aircraftInfo->setItem(8, 0, new QTableWidgetItem(aircraft.on_ground ? "✓" : "✖"));

    ui->TW_aircraftInfo->setVerticalHeaderItem(9, new QTableWidgetItem("Velocity, m/s"));
    if(aircraft.velocity_isNull) {
        ui->TW_aircraftInfo->setItem(9, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(9, 0, new QTableWidgetItem(QString::number(aircraft.velocity)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(10, new QTableWidgetItem("Course, °"));
    if(aircraft.true_track_isNull) {
        ui->TW_aircraftInfo->setItem(10, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(10, 0, new QTableWidgetItem(QString::number(aircraft.true_track)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(11, new QTableWidgetItem("Vertical rate, m/s"));
    if(aircraft.vertical_rate_isNull) {
        ui->TW_aircraftInfo->setItem(11, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(11, 0, new QTableWidgetItem(QString::number(aircraft.vertical_rate)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(12, new QTableWidgetItem("Sensors"));
    if(aircraft.sensors.isEmpty()) {
        ui->TW_aircraftInfo->setItem(12, 0, new QTableWidgetItem("———"));
    } else {
        QVector<int> sensors = aircraft.sensors;
        QString str = "";
        for(int i = 0; i < sensors.size(); ++i) {
            if(i != 0) {
                str.append(", ");
            }
            str.append(QString::number(sensors[i]));
        }
        ui->TW_aircraftInfo->setItem(12, 0, new QTableWidgetItem(str));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(13, new QTableWidgetItem("Geometric altitude, m"));
    if(aircraft.geo_altitude_isNull) {
        ui->TW_aircraftInfo->setItem(13, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(13, 0, new QTableWidgetItem(QString::number(aircraft.geo_altitude)));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(14, new QTableWidgetItem("Squawk"));
    if(aircraft.squawk_isNull) {
        ui->TW_aircraftInfo->setItem(14, 0, new QTableWidgetItem("———"));
    } else {
        ui->TW_aircraftInfo->setItem(14, 0, new QTableWidgetItem(aircraft.squawk));
    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(15, new QTableWidgetItem("Special purpose indicator"));
    ui->TW_aircraftInfo->setItem(15, 0, new QTableWidgetItem(aircraft.spi ? "✓" : "✖"));

    ui->TW_aircraftInfo->setVerticalHeaderItem(16, new QTableWidgetItem("Origin of state’s position"));
    switch(aircraft.position_source) {
    case OriginOfPosition::ASTERIX:
        ui->TW_aircraftInfo->setItem(16, 0, new QTableWidgetItem("ASTERIX"));
        break;

    case OriginOfPosition::Adsb:
        ui->TW_aircraftInfo->setItem(16, 0, new QTableWidgetItem("ADS-B"));
        break;

    case OriginOfPosition::FLARM:
        ui->TW_aircraftInfo->setItem(16, 0, new QTableWidgetItem("FLARM"));
        break;

    case OriginOfPosition::MLAT:
        ui->TW_aircraftInfo->setItem(16, 0, new QTableWidgetItem("MLAT"));
        break;

    }

    ui->TW_aircraftInfo->setVerticalHeaderItem(17, new QTableWidgetItem("Category"));
    switch(aircraft.category) {
    case AircraftCategory::ClusterObstacle:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Cluster Obstacle"));
        break;

    case AircraftCategory::EmergencyVehicle:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Surface Vehicle – Emergency Vehicle"));
        break;

    case AircraftCategory::Glider:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Glider / sailplane"));
        break;

    case AircraftCategory::Heavy:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Heavy (> 300000 lbs)"));
        break;

    case AircraftCategory::HighPerfomance:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("High Performance (> 5g acceleration and 400 kts)"));
        break;

    case AircraftCategory::HighVortexLarge:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("High Vortex Large (aircraft such as B-757)"));
        break;

    case AircraftCategory::Large:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Large (75000 to 300000 lbs)"));
        break;

    case AircraftCategory::Light:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Light (< 15500 lbs)"));
        break;

    case AircraftCategory::LighterThanAir:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Lighter-than-air"));
        break;

    case AircraftCategory::LineObstacle:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Line Obstacle"));
        break;

    case AircraftCategory::NoAdsbEmitterCategoryInformation:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("No ADS-B Emitter Category Information"));
        break;

    case AircraftCategory::NoInformationAtAll:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("No information at all"));
        break;

    case AircraftCategory::Parachutist:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Parachutist / Skydiver"));
        break;

    case AircraftCategory::PointObstacle:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Point Obstacle (includes tethered balloons)"));
        break;

    case AircraftCategory::Reserved:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Reserved"));
        break;

    case AircraftCategory::Rotocraft:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Rotorcraft"));
        break;

    case AircraftCategory::ServiceVehicle:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Surface Vehicle – Service Vehicle"));
        break;

    case AircraftCategory::Small:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Small (15500 to 75000 lbs)"));
        break;

    case AircraftCategory::Space:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Space / Trans-atmospheric vehicle"));
        break;

    case AircraftCategory::Ultralight:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Ultralight / hang-glider / paraglider"));
        break;

    case AircraftCategory::UnmannedAerialVehicle:
        ui->TW_aircraftInfo->setItem(17, 0, new QTableWidgetItem("Unmanned Aerial Vehicle"));
        break;
    }

    ui->TW_aircraftInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

AircraftInfoDialog::~AircraftInfoDialog()
{
    delete ui;
}

void AircraftInfoDialog::on_PB_ok_clicked() {
    close();
}

