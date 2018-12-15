#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T23:00:13
#
#-------------------------------------------------

QT       += core gui

windows {
    *-g++* {
        # MinGW
    }
    *-msvc* {
        # MSVC

QT       += webenginewidgets
    }
}

win32
{
QMAKE_CXXFLAGS += -std=c++17

}
macx
{
CONFIG   += C++11
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filehandler
TEMPLATE = app

RC_ICONS = xIcon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    fileworker.cpp \
    myapp.cpp \
    settingsWindow.cpp \
    fileinformation.cpp \
    mydatetime.cpp \
    textpathedit.cpp \
    pathchooserdialog.cpp \
    addfolderwidget.cpp \
    addfiledialog.cpp \
    pathline.cpp \
    mysplitterhandle.cpp \
    myverticalsplitter.cpp \
    myhorizontalsplitter.cpp \
    rulecontroller.cpp \
    rulepathselector.cpp \
    settingscontroller.cpp \
    rulepathdialogselector.cpp \
    abstractRuledialog.cpp \
    addruledialog.cpp \
    editruledialog.cpp \
    conditionWidget.cpp \
    baseworker.cpp

HEADERS  += mainwindow.h \
    messageBox.h \
    fileworker.h \
    myIcon.h \
    myapp.h \
    settingsWindow.h \
    myscreendimensions.h \
    fileinformation.h \
    mydatetime.h \
    mycombobox.h \
    textpathedit.h \
    pathchooserdialog.h \
    fileinformationview.h \
    addfolderwidget.h \
    addfiledialog.h \
    pathline.h \
    mysplitterhandle.h \
    myverticalsplitter.h \
    myhorizontalsplitter.h \
    rulecontroller.h \
    rulepathselector.h \
    settingscontroller.h \
    rulepathdialogselector.h \
    abstractRuleDialog.h \
    addruledialog.h \
    pathcontroller.h \
    editruledialog.h \
    conditionWidget.h \
    argumentvalues.h \
    ruledefinitions.h \
    baseworker.h \
    rules.h

FORMS    += mainwindow.ui \
    logger.ui \
    settingsWindow.ui \
    textpathedit.ui \
    pathchooserdialog.ui \
    addfolderwidget.ui \
    abstractRuledialog.ui \
    conditionWidget.ui

DISTFILES += \
    tempBuffer

RESOURCES += \
    myressource.qrc
