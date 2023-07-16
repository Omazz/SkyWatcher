#ifndef AIRCRAFTINFODIALOG_H
#define AIRCRAFTINFODIALOG_H

#include <QDialog>
#include "Requests/Aircraft.h"

namespace Ui {
class AircraftInfoDialog;
}

class AircraftInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AircraftInfoDialog(QWidget *parent = nullptr);


    ~AircraftInfoDialog();

    void setAircraftInfo(const Aircraft& aircraft);


private slots:
    void on_PB_ok_clicked();

private:
    Ui::AircraftInfoDialog *ui;

    Aircraft m_aircraft;
};

#endif // AIRCRAFTINFODIALOG_H
