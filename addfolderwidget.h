﻿#ifndef ADDFOLDERWIDGET_H
#define ADDFOLDERWIDGET_H

#include <QDialog>
#include <qdesktopwidget.h>
#include "pathline.h"
#include "addfiledialog.h"

#include <iostream>

using namespace std;

namespace Ui {
class AddFolderWidget;
}

class AddFolderWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AddFolderWidget();
    ~AddFolderWidget();

signals:
    void sendPath(QString path);

private slots:
    void sizeAdjust(QSizePolicy::Policy p,int H);
    void on_Add_Button_Clicked();

private:
    Ui::AddFolderWidget *ui;
    AddFileDialog *fileWidget;
    pathLine *pathWidget;
    QVBoxLayout *vLayout;
    int tempHeight;
};

#endif // ADDFOLDERWIDGET_H
