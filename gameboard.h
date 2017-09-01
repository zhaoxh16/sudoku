#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QApplication>
#include <QList>
#include "highlightframe.h"
#include "numberblock.h"
#include "boardcover.h"
#include "database.h"

typedef NumberBlock* NumberBlockPointer;

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = nullptr);
    void initializeGameBoard(int* numbers);//设置数独中预先填的数字
    void initializeGameBoard(QString numbers,QString isEditable, int usedTime, int level);
    void reset();
    void setLevel(int level);
    int* getNumbers();
    void setNumbers(int *numbers);
    void setEditable(bool *editable);
    QString getSavedNumbers();
    QString getSavedEditable();
    Database* database;


signals:
    void addNumberCommand(int* numbers, int count, NumberBlock* block);//记录所添加的数字
    void deleteNumberCommand(int* numbers, int count, NumberBlock* block);//记录所删除的数字
    void finish();//当数独被完成后发出该信号

public slots:
    void moveFocus(int number);
    void showHighlightFrame(int number);
    void showHighlightNumber(int number);
    void restart();
    void markFocusBlock();
    void judge();
    void clearFocusBlock();
    void changeNumberOnFocusBlock(int number);
    void setDatabase(Database* database);

protected:
    NumberBlockPointer blocks[81];
    HighlightFrame* rowFrame[9];
    HighlightFrame* columnFrame[9];
    BoardCover* boardCover;
    void paintEvent(QPaintEvent *event);
    int* sudokuNumbers;
};

#endif // GAMEBOARD_H
