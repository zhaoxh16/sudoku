#include "timer.h"

Timer::Timer(QWidget *parent) : QWidget(parent)
{
    isPausing = 1;
    timer = new QTimer(this);
    record = new QTime(0,0,0);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));

    hourLabel = new QLabel("00",this);
    hourLabel->setAlignment(Qt::AlignCenter);
    hourLabel->setFont(QFont("Academy Engraved LET",28));

    minuteLabel = new QLabel("00",this);
    minuteLabel->setAlignment(Qt::AlignCenter);
    minuteLabel->setFont(QFont("Academy Engraved LET",28));

    secondLabel = new QLabel("00",this);
    secondLabel->setAlignment(Qt::AlignCenter);
    secondLabel->setFont(QFont("Academy Engraved LET",28));

    QLabel* spacingLabel1 = new QLabel(":",this);
    spacingLabel1->setAlignment(Qt::AlignCenter);
    spacingLabel1->setFont(QFont("Academy Engraved LET",28));

    QLabel* spacingLabel2 = new QLabel(":",this);
    spacingLabel2->setAlignment(Qt::AlignCenter);
    spacingLabel2->setFont(QFont("Academy Engraved LET",28));

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->addWidget(hourLabel);
    layout->addWidget(spacingLabel1);
    layout->addWidget(minuteLabel);
    layout->addWidget(spacingLabel2);
    layout->addWidget(secondLabel);

    setLayout(layout);

}

void Timer::setTime(int usedTime){
    for(int i=0;i<usedTime;i++)
        *record = record->addSecs(1);
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

int Timer::getTime(){
    return record->hour()*3600+record->minute()*60+record->second();
}
