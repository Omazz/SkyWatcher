#include "AircraftInfoDialog.h"
#include "ui_AircraftInfoDialog.h"

AircraftInfoDialog::AircraftInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AircraftInfoDialog)
{
    ui->setupUi(this);
}


void AircraftInfoDialog::setAircraftInfo(Aircraft aircraft) {
    ui->TW_aircraftInfo->setRowCount(NUMBER_PARAMETERS);
    ui->TW_aircraftInfo->setColumnCount(1);
    ui->TW_aircraftInfo->setHorizontalHeaderItem(0, new QTableWidgetItem("Information"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(0, new QTableWidgetItem("ICAO-24"));
    ui->TW_aircraftInfo->setItem(0, 0, new QTableWidgetItem(aircraft.icao24));
    ui->TW_aircraftInfo->setVerticalHeaderItem(1, new QTableWidgetItem("Callsign"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(2, new QTableWidgetItem("Country"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(3, new QTableWidgetItem("Time position, s"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(4, new QTableWidgetItem("Last contact, s"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(5, new QTableWidgetItem("Longitude, °"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(6, new QTableWidgetItem("Latitude, °"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(7, new QTableWidgetItem("Barometric altitude, m"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(8, new QTableWidgetItem("On ground"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(9, new QTableWidgetItem("Velocity, m/s"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(10, new QTableWidgetItem("Course, °"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(11, new QTableWidgetItem("Vertical rate, m/s"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(12, new QTableWidgetItem("Sensors"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(13, new QTableWidgetItem("Geometric altitude, m"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(14, new QTableWidgetItem("Squawk"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(15, new QTableWidgetItem("Special purpose indicator"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(16, new QTableWidgetItem("Origin of state’s position"));
    ui->TW_aircraftInfo->setVerticalHeaderItem(17, new QTableWidgetItem("Category"));

    ui->TW_aircraftInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);




}

AircraftInfoDialog::~AircraftInfoDialog()
{
    delete ui;
}
