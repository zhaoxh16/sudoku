﻿#include "highlightframe.h"

HighlightFrame::HighlightFrame(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents,true);
}

void HighlightFrame::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    p->setRenderHint(QPainter::Antialiasing, true);\
    p->setPen(QPen(QColor(0,255,255,150),5));
    p->setBrush(Qt::transparent);
    p->drawRect(rect());
    delete p;
}
