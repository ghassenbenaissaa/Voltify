QT += core gui widgets sql charts serialport printsupport multimedia

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# Project structure
INCLUDEPATH += src

SOURCES += \
    src/arduino.cpp \
    src/client.cpp \
    src/connection.cpp \
    src/employee.cpp \
    src/fonction_st.cpp \
    src/insertdata.cpp \
    src/main.cpp \
    src/profil.cpp \
    src/reglage.cpp \
    src/service.cpp \
    src/station.cpp \
    src/stock.cpp

HEADERS += \
    src/arduino.h \
    src/client.h \
    src/connection.h \
    src/employee.h \
    src/fonction_st.h \
    src/insertdata.h \
    src/profil.h \
    src/reglage.h \
    src/service.h \
    src/station.h \
    src/stock.h

FORMS += \
    ui/client.ui \
    ui/employee.ui \
    ui/profil.ui \
    ui/reglage.ui \
    ui/service.ui \
    ui/station.ui \
    ui/stock.ui

TRANSLATIONS += \
    translations/charging_station_en_US.ts

RESOURCES += \
    resources/iconn.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
