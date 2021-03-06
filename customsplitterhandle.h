﻿#ifndef CUSTOMSPLITTERHANDLE_H
#define CUSTOMSPLITTERHANDLE_H

#include <QWidget>
#include <QSplitterHandle>
#include <qpaintengine.h>
#include <QPaintEvent>
#include <iostream>
#include <qlist.h>
#include <qsplitter.h>
#include <qlabel.h>
#include <qpen.h>

using namespace std;

class CustomSplitterHandle : public QSplitterHandle
{
public:
    CustomSplitterHandle(Qt::Orientation direction, QSplitter *parent = nullptr, QString label = QString());

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString handleLabel;
};

#endif // CUSTOMSPLITTERHANDLE_H
