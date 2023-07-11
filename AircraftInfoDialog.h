#ifndef AIRCRAFTINFODIALOG_H
#define AIRCRAFTINFODIALOG_H

#include <QDialog>
#include "Aircraft.h"

namespace Ui {
class AircraftInfoDialog;
}

class AircraftInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AircraftInfoDialog(QWidget *parent = nullptr);

    void setAircraftInfo(Aircraft aircraft);

    ~AircraftInfoDialog();

private:
    Ui::AircraftInfoDialog *ui;
};

#endif // AIRCRAFTINFODIALOG_H
