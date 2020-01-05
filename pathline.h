﻿#ifndef PATHLINE_H
#define PATHLINE_H

#include <qlineedit.h>
#include "abstracttextselectordialog.h"

class PathLine : public AbstractTextSelectorDialog
{
    Q_OBJECT

public:
    PathLine(QWidget *parent = nullptr);

signals:

    // Connected in forms editor
    void showFileExplorer();

protected:
    void on_toolButton_clicked();

private slots:
};

#endif // PATHLINE_H
