QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addpatient.cpp \
    configsettings.cpp \
    dbconnection.cpp \
    dialogaddvisit.cpp \
    dialogdbconnectionconfigure.cpp \
    dialogeditpatient.cpp \
    dialogviewvisits.cpp \
    exportdbdata.cpp \
    main.cpp \
    mainwindow.cpp \
    printvisit.cpp \
    searchpatient.cpp

HEADERS += \
    PROG_ENUMS.h \
    addpatient.h \
    configsettings.h \
    dbconnection.h \
    dialogaddvisit.h \
    dialogdbconnectionconfigure.h \
    dialogeditpatient.h \
    dialogviewvisits.h \
    exportdbdata.h \
    mainwindow.h \
    printvisit.h \
    searchpatient.h

FORMS += \
    addpatient.ui \
    dialogaddvisit.ui \
    dialogdbconnectionconfigure.ui \
    dialogeditpatient.ui \
    dialogviewvisits.ui \
    mainwindow.ui \
    searchpatient.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    hhc_resources.qrc

RC_ICONS = ./assets/app_icon/icon_256.ico
