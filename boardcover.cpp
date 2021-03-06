﻿#include "boardcover.h"

BoardCover::BoardCover(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents,true);
}

void BoardCover::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    //设置抗锯齿
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    if(!cover){
        p->setBrush(Qt::transparent);
        setAttribute(Qt::WA_TransparentForMouseEvents,true);
    }
    else{
        p->setBrush(Qt::gray);
        setAttribute(Qt::WA_TransparentForMouseEvents,false);
        this->setFocus();
    }
    //边框
    p->setPen(QPen(QColor(0,255,255,150),5));
    p->drawRect(rect());
    //画九个小九宫格之间的线条
    p->setPen(QPen(QColor(0,255,0,100),3));
    p->drawLine(QPoint(width()/3,0),QPoint(width()/3,height()));
    p->drawLine(QPoint(width()/3*2,0),QPoint(width()/3*2,height()));
    p->drawLine(QPoint(0,height()/3),QPoint(width(),height()/3));
    p->drawLine(QPoint(0,height()/3*2),QPoint(width(),height()/3*2));
    //画九个小九宫格里面的线条
    p->setPen(QPen(QColor(0,255,0,100),1));
    for(int i=1;i<9;i++){
        if(i!=3&&i!=6){
            p->drawLine(QPoint(width()/9*i,0),QPoint(width()/9*i,height()));
            p->drawLine(QPoint(0,height()/9*i),QPoint(width(),height()/9*i));
        }
    }
    delete p;
}

void BoardCover::setCover(bool isCover){
    if(isCover){
        cover = 1;
        update();
    }else{
        cover = 0;
        update();
    }
}
