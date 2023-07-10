QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AircraftRequester.cpp \
    AuthorizationForm.cpp \
    MapRequester.cpp \
    MapView.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    Aircraft.h \
    AircraftRequester.h \
    AuthorizationForm.h \
    GeoCalculator.h \
    MainWindow.h \
    MapRequester.h \
    MapView.h

FORMS += \
    AuthorizationForm.ui \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Recources/Map.png \
    Recources/SkyWatcherIcon.ico
