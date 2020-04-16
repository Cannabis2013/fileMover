#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T23:00:13
#
#-------------------------------------------------

QT       += core gui testlib

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
CONFIG   += C++17
}


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Filehandler
TEMPLATE = app


RC_ICONS = xIcon.ico

SOURCES += main.cpp\
    abstractframe.cpp \
    abstractruledialog.cpp \
    abstracttextselectordialog.cpp \
    applicationdomain.cpp \
    applicationui.cpp \
    conditionwidget.cpp \
    customdate.cpp \
    customdialog.cpp \
    customsplitter.cpp \
    customsplitterhandle.cpp \
    exceptionhandler.cpp \
    fileinformationmanager.cpp \
    fileinformationview.cpp \
    filepathdialogwidget.cpp \
    filesystemwatcher.cpp \
    fileworker.cpp \
    rulesmanager.cpp \
    settingsmanager.cpp \
    settingswindow.cpp \
    addfolderwidget.cpp \
    addfiledialog.cpp \
    rulepathselector.cpp \
    addruledialog.cpp \
    editruledialog.cpp \
    testfilecreator.cpp \
    threadsmanager.cpp \
    tst_core_functionality.cpp \
    topframeform.cpp

HEADERS  += \
    AbstractFileWorker.h \
    ISettingsWindowBuilder.h \
    abstractapplicationservice.h \
    abstractfileinformationmanager.h \
    abstractfileoperationworker.h \
    abstractfilesystemwatcher.h \
    abstractframe.h \
    abstracticon.h \
    abstractqueueManager.h \
    abstractruledialog.h \
    abstractpersistence.h \
    abstractrulesmanager.h \
    abstractsettingsmanager.h \
    abstracttextselectordialog.h \
    applicationdomain.h \
    applicationui.h \
    conditionwidget.h \
    customcombobox.h \
    customdate.h \
    customdialog.h \
    customsplitter.h \
    customsplitterhandle.h \
    defaultRuleConfiguration.h \
    defaultfilemodelscontext.h \
    defaultinjector.h \
    defaultsettingsarguments.h \
    directoryitem.h \
    entitymodel.h \
    entitymodelbuilder.h \
    entityqueuemanager.h \
    exceptionhandler.h \
    fileinformationmanager.h \
    filelistservice.h \
    filemodelbuilder.h \
    filepathdialogwidget.h \
    filescontext.h \
    filesystemwatcher.h \
    fileworker.h \
    filteringcontext.h \
    ibroadcastingobject.h \
    icon.h \
    idefaultrulescollection.h \
    ientitymodelbuilder.h \
    ifilelistservice.h \
    ifilemodel.h \
    ifiltereringcontext.h \
    imodel.h \
    imodelbuilder.h \
    imutableobject.h \
    inheritexceptiondelegate.h \
    irulebuilder.h \
    iruleconfiguration.h \
    iruledefinitions.h \
    iruleinterfaces.h \
    isettingsbuilder.h \
    isettingsmodel.h \
    isettingswindow.h \
    ithreadmanagerinterface.h \
    messageBox.h \
    rulebuilder.h \
    rulescontext.h \
    ruleservicesinjector.h \
    rulesmanager.h \
    myscreendimensions.h \
    settingsbuilder.h \
    settingsmanager.h \
    settingsmodel.h \
    settingsmodelbuilder.h \
    settingswindow.h \
    fileinformationview.h \
    addfolderwidget.h \
    addfiledialog.h \
    pathline.h \
    rulepathselector.h \
    addruledialog.h \
    editruledialog.h \
    ruledefinitions.h \
    rules.h \
    settingswindowbuilder.h \
    staticviewhelpers.h \
    testfilecreator.h \
    threaddescriptor.h \
    threadsmanager.h \
    topframeform.h

FORMS    += mainwindow.ui \
    conditionwidget.ui \
    customdialog.ui \
    logger.ui \
    settingswindow.ui \
    textpathedit.ui \
    addfolderwidget.ui \
    abstractruledialog.ui \
    filepathselectordialog.ui \
    topframeform.ui

DISTFILES += \
    tempBuffer

RESOURCES += \
    myressource.qrc
