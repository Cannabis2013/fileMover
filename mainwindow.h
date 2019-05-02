﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qpoint.h>
#include <qprocess.h>
#include <qdial.h>
#include <qfont.h>
#include <qscreen.h>
#include <qstringlist.h>
#include <qheaderview.h>
#include <qtextbrowser.h>
#include <qsplitter.h>
#include <qcheckbox.h>
#include <qevent.h>
#include <qtextstream.h>
#include <qthreadpool.h>
#include <qsharedpointer.h>
#include <math.h>
#include <qstackedwidget.h>
#include <QSystemTrayIcon>

#include "messageBox.h"
#include "myscreendimensions.h"
#include "fileinformationview.h"
#include "addfolderwidget.h"
#include "settingsWindow.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow,
        private IconScanner,
        private AbstractPersistence
{
    Q_OBJECT

public:
    explicit mainWindow(AbstractCoreApplication *coreApplication, QString appName, QString orgName);
    ~mainWindow();

    enum fontType{listFont,detailedList,labelFont,standardFont};
    enum dateSpecifier{day,month,year};

signals:

    void StartCount(QStringList ps);
    void toLog(QString t);
    void toLog(QStringList l);
    void quit(bool iH);

public slots:
    void setStatusText(QString txt);


protected:

    // Persistent Settings..
    void writeSettings();
    void readSettings();

    void closeEvent(QCloseEvent *cE);
    void keyPressEvent(QKeyEvent *kE);
    void keyReleaseEvent(QKeyEvent *kR);
    void mousePressEvent(QMouseEvent *mp);
    void mouseMoveEvent(QMouseEvent *e);


private slots:

    void updateViews();

    // Buttons..
    void on_addBut_clicked(); // Add path to "mainFolderView"
    void on_clearButt_clicked(); // The button slot that starts the "clear process"
    void on_countButt_clicked(); // Count number of items in the selected "path"
    void on_delButt_clicked(); // Delete an item in "mainFolderView"

    // countTimer related..
    void timerCount();
    void setTimerStatus(bool makeActive);

    // DetailedFolderView related..

    void detailedFolderMenuCalled(QPoint p);
    void openFolder(bool ok);
    void on_detailView_itemDoubleClicked(QTreeWidgetItem *item, int column);

    // Fileinformation & filesuffixlist related..
    void updateInfoScreen(QModelIndex index);
    void sortSuffixTreeColumn(int c);

    // Fileworker Related..
    void clearCompleted(bool a);
    void folderContentRecieved(QList<FileObject> sz);
    void actionCountFolder(bool f);

    // mainFolderView Related..
    void explorerFolder(bool ok);
    void contextMenuCalled(QPoint p);

    // Menu actions related..
    void on_actionIndstillinger_triggered();
    void on_actionQuit_triggered();

    // settingsWindow related..
    void iconSelected(QIcon ico);

    // Rules related..

    // statusLine related..

    void clearStatusLine();

    // Sub Tray Menu Related..
    void countMenuTriggered(QAction *cAction);
    void clearMenuTriggered(QAction *clAction);
    void explorerMenuTriggered(QAction *xAction);    

    // Systemtray Related..
    void tMenuClicked(QAction *a);
    void trayClicked(QSystemTrayIcon::ActivationReason res);
    void trayMsgClicked();
    void msgToTray(const QString &msg);

    void on_actionOpen_current_directory_triggered();

    void on_WatchFolderView_doubleClicked(const QModelIndex &index);

private:

    // Void member methods..

    // Add folder related..
    void updateViewIcons(QIcon ico);

    // Menu..
    void updateSubTrayMenus();

    // Systemtray related..
    void popSystemTrayMessage(const QString msg,const QString title = "Info");

    // Non-void Medlems Funktioner..

    //detailedFolderView related..
    void updateDetaileditems();
    void updateWatchFolderView();

    // General..
    double roundNumber(long long numb,QString &denote, int dec = 0);
    int fromSecondsToMilliseconds(int seconds){return seconds *1000;}
    int fromMinutesToMilliseconds(int minutes){return minutes *1000*60;}
    QFont createFont(fontType ft = fontType::standardFont, QString family = "Times New Roman",bool bold = false,bool italic = false, int staticSize = -1);
    QString modifyPath(QString s,QString S) const;
    QString mergeStringList(const QStringList &sList) const;
    QStringList splitString(const QString &split) const;
    QString currentMainFolderPath() const;

    //mainFolderView related..
    QStringList folders() const;
    QString folder(QString t) const;

    QFileInfoList fileItemList(const QStringList paths) const;

    // SuffixTree related..
    QList<QTreeWidgetItem*> sortSuffixes(QTreeWidget *sTree, const int column, Qt::SortOrder sortMode = Qt::AscendingOrder) const;
    QList<QTreeWidgetItem*> sortSuffixes(QList<QTreeWidgetItem*> sItems, Qt::SortOrder order = Qt::AscendingOrder) const;

    // Systemtray related..
    QIcon currentTrayIcon() const {return tray->icon();}

    // Member variables..
    Ui::mainWindow *ui;

    AbstractCoreApplication *coreApplication;

    bool countTimerStatus;
    fileInformationView *fileInfoBrowser;
    int tempKey,normalListFontSize, detailedListFontSize, countTimerInterval;    
    myScreenDimension laptopScreenSize, screenSize;
    QFont viewFont;    
    QHeaderView *suffixHeader;
    QIcon trayStandard,fileStandard;
    QKeyEvent *currentKeyEvent;
    QLineEdit *statusLine;
    QList<int>columnWidths;
    QMenu *trayMenu,*countTrayMenu,*clearTrayMenu,*folderTrayMenu,*mainFolderViewMenu, *detailedFolderViewMenu;
    QModelIndex menuIndex,viewTempIndex;
    QPoint offset;
    QPushButton *clBut;
    QSplitter hSplit,vSplit;
    QStackedWidget *buttonContainer;
    QString ePath,title,currentDir;
    QStringList directoriesToAppend;
    QSystemTrayIcon *tray;
    QTextBrowser *tBrowser;
    QTimer *countTimer, *clearStatusTextTimer;
    QTreeWidget *detailedFolderView, *suffixTree,*watchFolderView;
    QWidget *infBox;
};

#endif // MAINWINDOW_H
