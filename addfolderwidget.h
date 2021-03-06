﻿#ifndef ADDFOLDERWIDGET_H
#define ADDFOLDERWIDGET_H

#include <QDialog>
#include <qdesktopwidget.h>
#include "pathline.h"
#include "addfiledialog.h"
#include "abstractframe.h"

#include <iostream>

using namespace std;

namespace Ui {
class AddFolderWidget;
}

class AddFolderWidget : public AbstractFrame
{
    Q_OBJECT

public:
    explicit AddFolderWidget();
    ~AddFolderWidget();

signals:
    void sendPath(QString path);

protected:
    void resizeNotify(QSize newSize);

private slots:
    void sizeAdjust(QSizePolicy::Policy p,int H);
    void on_Add_Button_Clicked();

private:
    Ui::AddFolderWidget *ui;
    AddFileDialog *fileWidget;
    PathLine *pathWidget;
    QVBoxLayout *vLayout;
    int lastSavedHeight;
};

#endif // ADDFOLDERWIDGET_H
