﻿#include "mainform.h"

MainForm::MainForm(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(570);
    undoStack = new QUndoStack(this);
    gameBoard = new GameBoard(this);
    timer = new Timer(this);

    //toolBar = new QToolBar("Edit",this);
    QAction* undoAction = undoStack->createUndoAction(this,"undo");
    //toolBar->addAction(undoAction);
    QAction* redoAction = undoStack->createRedoAction(this,"redo");
   // toolBar->addAction(redoAction);

    startButton = new QPushButton("start",this);
    startButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton("pause",this);
    pauseButton->setFocusPolicy(Qt::NoFocus);
    restartButton = new QPushButton("restart",this);
    restartButton->setFocusPolicy(Qt::NoFocus);
    undoButton = new QPushButton("undo",this);
    undoButton->setFocusPolicy(Qt::NoFocus);
    redoButton = new QPushButton("redo", this);
    redoButton->setFocusPolicy(Qt::NoFocus);
    markButton = new QPushButton("mark",this);
    markButton->setFocusPolicy(Qt::NoFocus);
    solveButton = new QPushButton("solve",this);
    solveButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(pauseButton,SIGNAL(clicked(bool)),timer,SLOT(pause()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(restartButton,SIGNAL(clicked(bool)),gameBoard,SLOT(restart()));
    connect(undoButton,SIGNAL(clicked(bool)),undoAction,SLOT(trigger()));
    connect(redoButton,SIGNAL(clicked(bool)),redoAction,SLOT(trigger()));
    connect(markButton,SIGNAL(clicked(bool)),gameBoard,SLOT(markFocusBlock()));
    connect(solveButton,SIGNAL(clicked(bool)),this,SLOT(solve()));

    connect(gameBoard,SIGNAL(addNumberCommand(int*,int,NumberBlock*)),this,SLOT(addNumberCommand(int*,int,NumberBlock*)));
    connect(gameBoard,SIGNAL(deleteNumberCommand(int*,int,NumberBlock*)),this,SLOT(deleteNumberCommand(int*,int,NumberBlock*)));

    QVBoxLayout* layout = new QVBoxLayout(this);
    QGridLayout* topLayout = new QGridLayout;
    topLayout->setMargin(0);
    topLayout->setSpacing(1);

    topLayout->addWidget(timer,0,0);
    topLayout->addWidget(startButton,0,1);
    topLayout->addWidget(pauseButton,0,2);
    topLayout->addWidget(restartButton,0,3);
    topLayout->addWidget(markButton,0,4);
    topLayout->addWidget(undoButton,0,5);
    topLayout->addWidget(redoButton,0,6);
    topLayout->addWidget(solveButton,0,7);
    //layout->addWidget(toolBar);
    layout->addLayout(topLayout);
    layout->addWidget(gameBoard);

    //初始化gameBoard


    setLayout(layout);
}

void MainForm::addNumberCommand(int *numbers, int count, NumberBlock *block){
    undoStack->push(new AddNumbersCommand(numbers,count,block));
}

void MainForm::deleteNumberCommand(int *numbers, int count, NumberBlock *block){
    undoStack->push(new DeleteNumberCommand(numbers,count,block));
}

void MainForm::setLevel(int level){
    gameBoard->reset();
    gameBoard->setLevel(level);
    undoStack->clear();
    timer->start();
}

void MainForm::solve(){
    int *a = gameBoard->getNumbers();
    state myState = sudokuAlgorithm.initialState(a);
    state newState = sudokuAlgorithm.solve(myState);
    int b[81];
    for(int i=0;i<81;i++){
        for(int j=0;j<9;j++){
            if(newState.number[i]==1){
                b[i]=j+1;
                break;
            }
            else
                newState.number[i]/=2;
        }
    }
    gameBoard->setNumbers(b);
}
