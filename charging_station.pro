QT+= sql
QT       += core gui printsupport
QT       += core sql
QT       += charts
QT += multimedia
QT       += core gui  serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    connection.cpp \
    employee.cpp \
    main.cpp \
    profil.cpp \
    reglage.cpp \
    service.cpp \
    station.cpp \
    stock.cpp

HEADERS += \
    arduino.h \
    client.h \
    connection.h \
    employee.h \
    profil.h \
    reglage.h \
    service.h \
    station.h \
    stock.h

FORMS += \
    client.ui \
    employee.ui \
    profil.ui \
    reglage.ui \
    service.ui \
    station.ui \
    stock.ui

TRANSLATIONS += \
    charging_station_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iconn.qrc

DISTFILES += \
    ICON/326132086_1377220566362323_2334973245028434171_n.png \
    ICON/326253185_1247096072879450_2122464190835713788_n.png \
    ICON/326421902_3390623604598503_20181722436645681_n.png
