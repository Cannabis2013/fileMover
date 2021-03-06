﻿#ifndef ADDFILEDIALOG_H
#define ADDFILEDIALOG_H

#include "filepathdialogwidget.h"
#include <qsizepolicy.h>
#include <QModelIndex>

class AddFileDialog : public filepathDialogWidget
{
    Q_OBJECT
public:
    AddFileDialog(QWidget *parent);

public slots:
    void hideExplorer();
    void setCurrentIndex(QString txt);

signals:
    void quitSignal();
    void shrinkWindow(QSizePolicy::Policy p,int Height);
    void sendCurrentFilePath(QString fp);
    void addButtonClicked();

protected slots:
    void on_insertPathButton_clicked();
private slots:
    void on_cancelButton_clicked();
    void currentFilePath(QModelIndex fileIndex);

private:
    QFileSystemModel *fileModel;
    QTreeView *view;
};

#endif // ADDFILEDIALOG_H
