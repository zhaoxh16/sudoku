#include "timer.h"

Timer::Timer(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    record = new QTime(0,0,0);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    hourLabel = new QLabel("0",this);
    hourLabel->setFixedSize(40,20);
    minuteLabel = new QLabel("0",this);
    minuteLabel->setFixedSize(40,20);
    secondLabel = new QLabel("0",this);
    secondLabel->setFixedSize(40,20);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(hourLabel);
    hLayout->addWidget(minuteLabel);
    hLayout->addWidget(secondLabel);

    setLayout(hLayout);
}

void Timer::updateTime(){
    *record = record->addSecs(1);
    //更新显示的时间
    hourLabel->setText(QVariant(record->hour()).toString());
    minuteLabel->setText(QVariant(record->minute()).toString());
    secondLabel->setText(QVariant(record->second()).toString());
}

void Timer::start(){
    timer->start(1000);
}

void Timer::pause(){
    timer->stop();
}

void Timer::stop(){
    timer->stop();
    record->setHMS(0,0,0);
    hourLabel->setText("0");
    minuteLabel->setText("0");
    secondLabel->setText("0");
}
