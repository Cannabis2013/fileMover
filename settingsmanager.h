#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QTimer>
#include <qstring.h>
#include <QTreeWidgetItem>
#include "qlist.h"
#include "abstractpersistence.h"
#include "icon.h"
#include <qdir.h>
#include <qdiriterator.h>
#include "isettingsdelegate.h"
#include "entitymodel.h"
#include "imutableobject.h"
#include <qdatastream.h>
#include <settingsdelegate.h>
#include "abstractsettingsmanager.h"


class settingsManager : public AbstractSettingsManager,
        private AbstractPersistence
{
    Q_OBJECT
public:
    settingsManager(const QString &appName, const QString &orgName);
    ~settingsManager();

    // Persistence
    void readSettings() override;
    void writeSettings() override;

    // Basic settings
    void setCloseOnExit(bool enable) override;
    void setRulesEnabled(bool enable) override;
    void setTimerEnabled(bool enable) override;
    void setTimerInterval(int msec) override;

    // Icons
    void insertIcon(const AbstractIcon *ic) override {trayIconList << ic;}
    void insertIcons(const QList<const AbstractIcon*> &icons) override {trayIconList << icons;}

    const ISettingsDelegate* settingsState() const override;
    void setSettings(const ISettingsDelegate *s) override;

    // Path Related..

    int folderCount() const override {return watchFolders.count();}

    void insertPath(QString path) override;
    void insertPath(const QStringList& paths) override;

    void removePath(QString path) override;
    void removePathAt(int index) override;
    void clearPaths() override;

    // Request file object processing

    void requestProcess();

    QStringList paths() const override {return watchFolders;}
    QList<QTreeWidgetItem *> pathItems() const override;

    bool closeOnQuit() const override {return _settings->closeOnExit();}
    bool isRulesEnabled() const override {return _settings->rulesEnabled();}
    bool countTimerEnabled() const override {return _settings->ruleTimerEnabled();}
    QString countTimerInterval() const override {return QString::number(_settings->ruleCountInterval());}

    // Icons related..
    QList<const AbstractIcon*> allIcons() const override {return trayIconList;}

private:
    QList<const AbstractIcon *> scanForIcons(QString path);
    QStringList watchFolders;
    QString ressourceFolder = "Ressources";
    QString fileIconPath = "fileIcons";
    const ISettingsDelegate* _settings;
    QTimer countTimer;
    QList<const AbstractIcon*> trayIconList;
    QList<const AbstractIcon*> fileIconList;
    const AbstractIcon *currentTrayIcon;
    const AbstractIcon * fileIconStandard;

};

typedef settingsManager sM;

#endif // SETTINGSCONTROLLER_H
