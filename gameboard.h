#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include "highlightframe.h"
#include "numberblock.h"

typedef NumberBlock* NumberBlockPointer;

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);

signals:

public slots:
    void moveFocus(int number);
    void showHighlightFrame(int number);
    void showHighlightNumber(int number);
    void restart();

protected:
    NumberBlockPointer blocks[81];
    HighlightFrame* rowFrame[9];
    HighlightFrame* columnFrame[9];
    void paintEvent(QPaintEvent *event);
};

#endif // GAMEBOARD_H
