#include "timer.h"

Timer::Timer(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(70);
    isPausing = 1;
    timer = new QTimer(this);
    record = new QTime(0,0,0);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    hourLabel = new QLabel("00",this);
    hourLabel->setFixedWidth(20);
    hourLabel->setAlignment(Qt::AlignCenter);
    minuteLabel = new QLabel("00",this);
    minuteLabel->setFixedWidth(20);
    minuteLabel->setAlignment(Qt::AlignCenter);
    secondLabel = new QLabel("00",this);
    secondLabel->setFixedWidth(20);
    secondLabel->setAlignment(Qt::AlignCenter);
    QLabel* spacingLabel1 = new QLabel(":",this);
    QLabel* spacingLabel2 = new QLabel(":",this);
    spacingLabel2->setScaledContents(true);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setSpacing(0);
    hLayout->setMargin(0);
    hLayout->addWidget(hourLabel);
    hLayout->addWidget(spacingLabel1);
    hLayout->addWidget(minuteLabel);
    hLayout->addWidget(spacingLabel2);
    hLayout->addWidget(secondLabel);

    setLayout(hLayout);
}

void Timer::updateTime(){
    *record = record->addSecs(1);

    //更新显示的时间
    if(record->hour()<10)
        hourLabel->setText("0"+QVariant(record->hour()).toString());
    else
        hourLabel->setText(QVariant(record->hour()).toString());

    if(record->minute()<10)
        minuteLabel->setText("0"+QVariant(record->minute()).toString());
    else
        minuteLabel->setText(QVariant(record->minute()).toString());

    if(record->second()<10)
        secondLabel->setText("0"+QVariant(record->second()).toString());
    else
        secondLabel->setText(QVariant(record->second()).toString());
}

void Timer::start(){
    timer->start(1000);
    isPausing = 0;
}

void Timer::pause(){
    timer->stop();
    isPausing = 1;
}

void Timer::changeState(){
    if(isPausing)
        start();
    else
        pause();
}

void Timer::stop(){
    timer->stop();
    record->setHMS(0,0,0);
    hourLabel->setText("00");
    minuteLabel->setText("00");
    secondLabel->setText("00");
}
