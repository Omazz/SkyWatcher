#ifndef AIRCRAFTINFOBUTTON_H
#define AIRCRAFTINFOBUTTON_H

#include <QPushButton>
#include "Aircraft.h"

class AircraftInfoButton : public QPushButton
{
    Q_OBJECT
public:
    AircraftInfoButton();

    void setAircraft(const Aircraft& aircraft);

    Aircraft getAircraft();

private:
   Aircraft m_aircraft;
};

#endif // AIRCRAFTINFOBUTTON_H
