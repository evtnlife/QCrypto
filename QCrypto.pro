#-------------------------------------------------
#
# Project created by QtCreator 2016-10-13T23:30:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += crypto
TARGET = QCrypto
TEMPLATE = app


SOURCES += main.cpp\
        qcrypto.cpp \
    issecurebuild.cpp

HEADERS  += qcrypto.h \
    issecurebuild.h

FORMS    += qcrypto.ui

INCLUDEPATH += C:/QCA/include/QtCrypto

LIBS += -L"C:/QCA/lib"
LIBS += -lqca
LIBS += -L"C:/QCA/lib/qca/crypto" -lqca-ossl -lqca-gnupg -lqca-logger -lqca-softstore
