#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QWidget>
#include <qframe.h>
#include <qgridlayout.h>
#include <QMouseEvent>
#include <QCloseEvent>
#include <qpoint.h>
#include <qsizepolicy.h>
#include <iostream>
#include <memory>
#include <qpointer.h>
#include <qscreen.h>

#include "ui_customdialog.h"
#include "imutableobject.h"
#include "abstractframe.h"

using namespace std;

namespace Ui {
    class CustomDialog;
}

class CustomDialog :
        public QWidget,
        public IMutableObject
{
    Q_OBJECT

public:
    enum widget_Location {center_on_screen,center_according_to_parent, default_location};
    explicit CustomDialog(AbstractFrame *implementable,
                          bool applicationModal = true, widget_Location location = center_on_screen,
                          QWidget *parent = nullptr);
    ~CustomDialog();

    void setFrameTitle(QString title);
    QString FrameTitle();

    AbstractFrame *containedWidget(){return mainWidget;}

    void setWidget(AbstractFrame *implementable);

signals:
    void stateChanged();
protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private slots:

    void on_exitButton_clicked();

    void moveGlobalEvent(QPoint pos);
    void widgetSizeChanged(QSize newSize);

private:
    void setPosition(widget_Location location);
    void setSize(QSize size);
    void show_centered_on_screen();

    Ui::CustomDialog *ui;
    bool isMouseButtonPressed = false;
    QFrame *widgetContainer;
    int eventThreshold;
    TopFrameForm *topFrame;
    QPointer<AbstractFrame> mainWidget;
    QGridLayout *widgetGridLayout;
    QVBoxLayout *mainLayout;

    QPoint mousePressPosition;
    QRect tempGeometry;
    QSize widgetSize;

public:
};

#endif // CUSTOMDIALOG_H
