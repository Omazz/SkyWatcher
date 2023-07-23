QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/AircraftGraphicsItem.cpp \
    GUI/AircraftInfoButton.cpp \
    GUI/AircraftInfoDialog.cpp \
    GUI/AircraftScene.cpp \
    GUI/MainWindow.cpp \
    GUI/MapView.cpp \
    Requests/AircraftRequester.cpp \
    Requests/AircraftTimer.cpp \
    Requests/MapRequester.cpp \
    main.cpp

HEADERS += \
    GUI/AircraftGraphicsItem.h \
    GUI/AircraftInfoButton.h \
    GUI/AircraftInfoDialog.h \
    GUI/AircraftScene.h \
    GUI/MainWindow.h \
    GUI/MapView.h \
    Requests/Aircraft.h \
    Requests/AircraftRequester.h \
    Requests/AircraftTimer.h \
    Requests/MapRequester.h

FORMS += \
    GUI/AircraftInfoDialog.ui \
    GUI/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


TARGET = SkyWatcher

DESTDIR = ../Build-SkyWatcher

OBJECTS_DIR = ../Build-SkyWatcher

MOC_DIR = ../Build-SkyWatcher

UI_DIR = ../Build-SkyWatcher

DISTFILES += \
    Recources/LoadingScreen.jpg \
    Recources/Map.png \
    Recources/SkyWatcherIcon.ico

include(PriFiles/GeographicCoordsHandler/geographicCoordsHandler.pri)
include(PriFiles/LoadingScreen/loadingScreen.pri)
