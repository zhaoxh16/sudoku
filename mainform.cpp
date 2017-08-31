#include "mainform.h"

MainForm::MainForm(QWidget *parent) : QWidget(parent)
{
    setFixedSize(850,660);

    undoStack = new QUndoStack(this);
    QAction* undoAction = undoStack->createUndoAction(this,"undo");
    QAction* redoAction = undoStack->createRedoAction(this,"redo");

    gameBoard = new GameBoard(this);
    gameBoard->move(20,20);

    title = new QLabel("Level 10", this);
    title->resize(260,60);
    title->move(590,40);
    title->setFont(QFont("Academy Engraved LET",38));
    title->setStyleSheet("color:blue");

    timer = new Timer(this);
    timer->move(580,120);

    startButton = new QPushButton("开始/暂停",this);
    startButton->setFocusPolicy(Qt::NoFocus);
    startButton->resize(211,61);
    startButton->move(600,210);
    startButton->setFont(QFont("楷体",18));
    connect(startButton,SIGNAL(clicked(bool)),timer,SLOT(changeState()));

    restartButton = new QPushButton("重新开始",this);
    restartButton->setFocusPolicy(Qt::NoFocus);
    restartButton->resize(211,61);
    restartButton->move(600,290);
    restartButton->setFont(QFont("楷体",18));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(restartButton,SIGNAL(clicked(bool)),gameBoard,SLOT(restart()));

    exitButton = new QPushButton("主菜单",this);
    exitButton->setFocusPolicy(Qt::NoFocus);
    exitButton->resize(211,61);
    exitButton->move(600,370);
    exitButton->setFont(QFont("楷体",18));

    undoButton = new QPushButton("撤销",this);
    undoButton->setFocusPolicy(Qt::NoFocus);
    undoButton->resize(100,40);
    undoButton->move(600,510);
    undoButton->setFont(QFont("华文新魏",14));
    connect(undoButton,SIGNAL(clicked(bool)),undoAction,SLOT(trigger()));

    redoButton = new QPushButton("重做", this);
    redoButton->setFocusPolicy(Qt::NoFocus);
    redoButton->resize(100,40);
    redoButton->move(710,510);
    redoButton->setFont(QFont("华文新魏",14));
    connect(redoButton,SIGNAL(clicked(bool)),redoAction,SLOT(trigger()));

    markButton = new QPushButton("标记",this);
    markButton->setFocusPolicy(Qt::NoFocus);
    markButton->resize(100,40);
    markButton->move(600,460);
    markButton->setFont(QFont("华文新魏",14));
    connect(markButton,SIGNAL(clicked(bool)),gameBoard,SLOT(markFocusBlock()));

    deleteButton = new QPushButton("清除",this);
    deleteButton->setFocusPolicy(Qt::NoFocus);
    deleteButton->resize(100,40);
    deleteButton->move(710,460);
    deleteButton->setFont(QFont("华文新魏",14));
    connect(deleteButton,SIGNAL(clicked(bool)),gameBoard,SLOT(clearFocusBlock()));

    hintButton = new QPushButton("提示",this);
    hintButton->setFocusPolicy(Qt::NoFocus);
    hintButton->resize(100,40);
    hintButton->move(600,590);
    hintButton->setFont(QFont("华文新魏",14));

    solveButton = new QPushButton("答案",this);
    solveButton->setFocusPolicy(Qt::NoFocus);
    solveButton->resize(100,40);
    solveButton->move(710,590);
    solveButton->setFont(QFont("华文新魏",14));
    connect(solveButton,SIGNAL(clicked(bool)),this,SLOT(solve()));

    connect(gameBoard,SIGNAL(addNumberCommand(int*,int,NumberBlock*)),this,SLOT(addNumberCommand(int*,int,NumberBlock*)));
    connect(gameBoard,SIGNAL(deleteNumberCommand(int*,int,NumberBlock*)),this,SLOT(deleteNumberCommand(int*,int,NumberBlock*)));

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
    undoStack->clear();
    int *a = gameBoard->getNumbers();
    sudokuAlgorithm.reset();
    state myState = sudokuAlgorithm.initializeState(a);
    //测试
    //int solutionNumber = sudokuAlgorithm.getSolutionNumber(myState);
    //qDebug()<<solutionNumber;
    //sudokuAlgorithm.reset();
    //测试结束
    state newState = sudokuAlgorithm.solve(myState);
    int *b = new int[81];
    for(int i=0;i<81;i++){
        for(int j=0;j<9;j++){
            if(newState.number[i]==0)
                b[i] = 0;
            else if(newState.number[i]==1){
                b[i]=j+1;
                break;
            }
            else
                newState.number[i]/=2;
        }
    }

    gameBoard->setNumbers(b);
}
