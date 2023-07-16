#include "AircraftInfoButton.h"

AircraftInfoButton::AircraftInfoButton()
{

}


void AircraftInfoButton::setAircraft(const Aircraft& aircraft) {
    m_aircraft = aircraft;
}

Aircraft AircraftInfoButton::getAircraft() {
    return m_aircraft;
}
