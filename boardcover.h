#ifndef BOARDCOVER_H
#define BOARDCOVER_H

#include <QWidget>
#include <QPainter>

class BoardCover : public QWidget
{
    Q_OBJECT
public:
    explicit BoardCover(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BOARDCOVER_H
