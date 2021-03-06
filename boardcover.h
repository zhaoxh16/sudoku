﻿#ifndef BOARDCOVER_H
#define BOARDCOVER_H

#include <QWidget>
#include <QPainter>

class BoardCover : public QWidget
{
    Q_OBJECT
public:
    explicit BoardCover(QWidget *parent = nullptr);
    void setCover(bool isCover);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    bool cover = 0;
};

#endif // BOARDCOVER_H
