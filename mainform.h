#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include "gameboard.h"
#include <QGridLayout>
#include "timer.h"
#include <QPushButton>
#include <QHBoxLayout>

class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(QWidget *parent = nullptr);

signals:

public slots:

private:
    GameBoard* gameBoard;
    Timer* timer;
    QPushButton* startButton;
    QPushButton* pauseButton;
    QPushButton* restartButton;
};

#endif // MAINFORM_H
