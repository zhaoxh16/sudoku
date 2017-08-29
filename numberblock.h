#ifndef NUMBERBLOCK_H
#define NUMBERBLOCK_H

#include <QWidget>
#include <QPalette>
#include <QLineEdit>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QVariant>

class NumberBlock : public QWidget
{
    Q_OBJECT
public:
    explicit NumberBlock(QWidget *parent = nullptr);
    void setEditable(bool editable);
    void setNumber(int number);
    int getNumber();

signals:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void highlight(int number);

public slots:


protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    QLabel* label;
    QLabel* smallLabel[9];
    bool editable = 1;
    int usedSmallLabel = 0;
};

#endif // NUMBERBLOCK_H
