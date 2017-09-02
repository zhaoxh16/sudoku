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
#include <QDebug>
#include "sudokualgorithm.h"
#include "undomodule.h"

class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = nullptr);
    void setLevel(int level);
    void setTitle(QString text);
    void setGame(QString numbers, QString isEditable, int usedTime,int level);

signals:
    void exitToMenu();//返回主菜单
    void setDatabase(Database* database);
    void youWin();

public slots:
    void addNumberCommand(int* numbers, int count, NumberBlock* block);//记录所添加的数字
    void deleteNumberCommand(int* numbers, int count, NumberBlock* block);//记录所删除的数字
    void solve();
    void getSolutions();
    void reset();
    void changeStartButtonText();
    void save();
    void restart();
    void finish();//当数独被完成后执行

protected:
    void paintEvent(QPaintEvent *event);

private:
    GameBoard* gameBoard;
    Timer* timer;
    QPushButton* startButton;
    QPushButton* exitButton;
    QPushButton* restartButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* markButton;
    QPushButton* deleteButton;
    QPushButton* hintButton;
    QPushButton* solveButton;
    QPushButton* saveButton;
    QUndoStack* undoStack;
    SudokuAlgorithm sudokuAlgorithm;
    QLabel* title;
    QPushButton* numberButton[9];
};

#endif // MAINFORM_H
