#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T17:17:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeeklyReportHelp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    projectitemwidget.cpp

HEADERS += \
        mainwindow.h \
    projectitemwidget.h

FORMS += \
        mainwindow.ui \
    projectitemwidget.ui

SMTP_LOCATION = $$PWD/SMTPEmail
SMTP_LIBRARY_LOCATION = $$SMTP_LOCATION/bin
SMTP_INCLUDE_LOCATION = $$SMTP_LOCATION/include

win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lSMTPEmail
else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSMTPEmail

INCLUDEPATH += $$SMTP_INCLUDE_LOCATION
DEPENDPATH += $$SMTP_LIBRARY_LOCATION
