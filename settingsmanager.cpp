#include "settingsmanager.h"

settingsManager::settingsManager(QString appName, QString orgName):
    AbstractPersistence (appName,orgName)
{
    QList<MyIcon> trayIconList = iconsFromPath(ressourceFolder);

    QDir dir;
    if(!dir.exists(ressourceFolder))
        dir.mkdir(ressourceFolder);
    if(!dir.exists(fileIconPath))
        dir.mkdir(fileIconPath);

    if(trayIconList.count() == 0)
        currentTrayIcon = QIcon(":/My Images/Ressources/Hdd-icon.png");
    else
    {
        insertIcons(trayIconList);
        currentTrayIcon = trayIconList.last();
    }

    fileIconList = iconsFromPath(fileIconPath);
    if(!fileIconList.isEmpty())
        fileIconStandard = fileIconList.last();
}

settingsManager::~settingsManager()
{
    writeSettings();
}

void settingsManager::insertPath(QString path)
{
    mainFolderPaths << path;
    emit processPath(path);
    emit stateChanged();
}

void settingsManager::insertPaths(QStringList paths)
{
    mainFolderPaths << paths;
    emit processPaths(paths);
    emit stateChanged();
}

void settingsManager::removePath(QString path)
{
    mainFolderPaths.removeOne(path);
    emit removeItem(path);
    emit stateChanged();
}

void settingsManager::removePathAt(int index)
{
    mainFolderPaths.removeAt(index);
    emit stateChanged();
}

QList<QTreeWidgetItem *> settingsManager::pathItems()
{
    QList<QTreeWidgetItem*> items;
    for (QString path : mainFolderPaths) {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem();
        treeItem->setText(0,path);
        items << treeItem;
    }
    return items;
}

void settingsManager::readSettings()
{
    persistenceSettings->beginGroup("Settings");

    closeOnExit = persistenceSettings->value("Close on exit",true).toBool();
    timerMsec = persistenceSettings->value("Count timer interval", 2000).toInt();
    rulesEnabled = persistenceSettings->value("Rules enabled", false).toBool();

    persistenceSettings->endGroup();

    int count = persistenceSettings->beginReadArray("Watchfolders");
    QStringList folders;
    for (int i = 0;i < count;i++)
        folders << persistenceSettings->value(QString("Folder (%1)").arg(i)).toString();

    insertPaths(folders);
    persistenceSettings->endArray();
}

void settingsManager::writeSettings()
{
    persistenceSettings->beginGroup("Settings");

    persistenceSettings->setValue("Close on exit", closeOnExit);
    persistenceSettings->setValue("Count timer interval", timerMsec);
    persistenceSettings->setValue("Rules enabled", rulesEnabled);

    persistenceSettings->endGroup();

    persistenceSettings->beginWriteArray("Watchfolders", mainFolderPaths.count());

    for(int i = 0;i < mainFolderPaths.count();i++)
    {
        QString path = mainFolderPaths.at(i);
        QString keyVal = QString("Folder (%1)").arg(i);
        persistenceSettings->setValue(keyVal,path);
        persistenceSettings->setArrayIndex(i);
    }
    persistenceSettings->endArray();
}