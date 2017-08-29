#include "mainform.h"

MainForm::MainForm(QWidget *parent) : QWidget(parent)
{
    gameBoard = new GameBoard(this);
    timer = new Timer(this);
    startButton = new QPushButton("start",this);
    pauseButton = new QPushButton("pause",this);
    restartButton = new QPushButton("restart",this);
    connect(startButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(pauseButton,SIGNAL(clicked(bool)),timer,SLOT(pause()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(restartButton,SIGNAL(clicked(bool)),gameBoard,SLOT(restart()));

    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(timer);
    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(restartButton);
    layout->addLayout(topLayout);
    layout->addWidget(gameBoard);



    setLayout(layout);
}
