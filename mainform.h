#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include "gameboard.h"
#include <QGridLayout>
#include "timer.h"
#include <QPushButton>
#include <QToolButton>
#include <QHBoxLayout>
#include <QUndoStack>
#include <QToolBar>
#include "sudokualgorithm.h"
#include "undomodule.h"

class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = nullptr);
    void setLevel(int level);

signals:

public slots:
    void addNumberCommand(int* numbers, int count, NumberBlock* block);//记录所添加的数字
    void deleteNumberCommand(int* numbers, int count, NumberBlock* block);//记录所删除的数字
    void solve();

private:
    GameBoard* gameBoard;
    Timer* timer;
    QPushButton* startButton;
    QPushButton* pauseButton;
    QPushButton* restartButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* markButton;
    QPushButton* solveButton;
    QUndoStack* undoStack;
    SudokuAlgorithm sudokuAlgorithm;
};

#endif // MAINFORM_H
