QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    employeesdbmanager.cpp \
    presenter_qml.cpp \
    employee.cpp \
    hourlypaidemployee.cpp \
    monthlypaidemployee.cpp \
    salesemployee.cpp \
    employeesmanager.cpp \
    employeesinterfacetodb.cpp

#RESOURCES += qml.qrc
RESOURCES += \
    testQRC.qrc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    Test.qml \
    test.json \
    employeesDB.json \
    Splash.qml \
    IntroductoryImage.png \
    test_file.json \
    Chart.qml

HEADERS += \
    employeesdbmanager.h \
    employee.h \
    presenter_qml.h \
    monthlypaidemployee.h \
    hourlypaidemployee.h \
    salesemployee.h \
    employeesmanager.h \
    employeesinterfacetodb.h




