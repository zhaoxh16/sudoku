#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QApplication>
#include "highlightframe.h"
#include "numberblock.h"

typedef NumberBlock* NumberBlockPointer;

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);
    void initializeGameBoard(int* numbers);//设置数独中预先填的数字

signals:
    void addNumberCommand(int* numbers, int count, NumberBlock* block);//记录所添加的数字
    void deleteNumberCommand(int* numbers, int count, NumberBlock* block);//记录所删除的数字

public slots:
    void moveFocus(int number);
    void showHighlightFrame(int number);
    void showHighlightNumber(int number);
    void restart();
    void markFocusBlock();

protected:
    NumberBlockPointer blocks[81];
    HighlightFrame* rowFrame[9];
    HighlightFrame* columnFrame[9];
    void paintEvent(QPaintEvent *event);
};

#endif // GAMEBOARD_H
