#ifndef TIMER_H
#define TIMER_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QHBoxLayout>
#include <QVariant>

class Timer : public QWidget
{
    Q_OBJECT
public:
    explicit Timer(QWidget *parent = nullptr);
    void setTime(int usedTime);
    int getTime();//以秒为单位

signals:

public slots:
    void updateTime();
    void start();
    void pause();
    void stop();
    void changeState();

private:
    QTimer* timer;
    QTime* record;
    QLabel* hourLabel;
    QLabel* minuteLabel;
    QLabel* secondLabel;
    bool isPausing;
};

#endif // TIMER_H
