#include "mainform.h"

MainForm::MainForm(QWidget *parent) : QWidget(parent)
{
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

    connect(startButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(pauseButton,SIGNAL(clicked(bool)),timer,SLOT(pause()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(restartButton,SIGNAL(clicked(bool)),gameBoard,SLOT(restart()));
    connect(undoButton,SIGNAL(clicked(bool)),undoAction,SLOT(trigger()));
    connect(redoButton,SIGNAL(clicked(bool)),redoAction,SLOT(trigger()));
    connect(markButton,SIGNAL(clicked(bool)),gameBoard,SLOT(markFocusBlock()));

    connect(gameBoard,SIGNAL(addNumberCommand(int*,int,NumberBlock*)),this,SLOT(addNumberCommand(int*,int,NumberBlock*)));
    connect(gameBoard,SIGNAL(deleteNumberCommand(int*,int,NumberBlock*)),this,SLOT(deleteNumberCommand(int*,int,NumberBlock*)));

    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(timer);
    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(restartButton);
    topLayout->addWidget(markButton);
    topLayout->addWidget(undoButton);
    topLayout->addWidget(redoButton);
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
}
