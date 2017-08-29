#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    GameBoard* gameBoard = new GameBoard(this);
    setCentralWidget(gameBoard);
}

MainWindow::~MainWindow()
{

}
