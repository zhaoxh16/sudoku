﻿#include "chooselevelwidget.h"
#include "ui_chooselevelwidget.h"

ChooseLevelWidget::ChooseLevelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseLevelWidget)
{
    ui->setupUi(this);
    pushButton[0]=ui->pushButton;
    pushButton[1]=ui->pushButton_2;
    pushButton[2]=ui->pushButton_3;
    pushButton[3]=ui->pushButton_4;
    pushButton[4]=ui->pushButton_5;
    pushButton[5]=ui->pushButton_6;
    pushButton[6]=ui->pushButton_7;
    pushButton[7]=ui->pushButton_8;
    pushButton[8]=ui->pushButton_9;
    pushButton[9]=ui->pushButton_10;

    QSignalMapper* mapper = new QSignalMapper;
    for(int i=0;i<10;i++){
        connect(pushButton[i],SIGNAL(clicked(bool)),mapper,SLOT(map()));
        mapper->setMapping(pushButton[i],i+1);
    }
    connect(mapper,SIGNAL(mapped(int)),this,SIGNAL(chooseLevel(int)));
    setStyleSheet(".QPushButton{background:rgb(0,225,255,50)}");

}

ChooseLevelWidget::~ChooseLevelWidget()
{
    delete ui;
}

void ChooseLevelWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    p->setBrush(QColor(255,250,205,100));
    p->setPen(Qt::transparent);
    p->drawRect(rect());
    delete p;
}
