#include "mainform.h"

MainForm::MainForm(QWidget *parent) : QWidget(parent)
{
    setFixedSize(940,580);

    undoStack = new QUndoStack(this);
    QAction* undoAction = undoStack->createUndoAction(this,"undo");
    QAction* redoAction = undoStack->createRedoAction(this,"redo");

    gameBoard = new GameBoard(this);
    gameBoard->move(20,20);

    title = new QLabel("Level 10", this);
    title->resize(260,60);
    title->move(680,40);
    title->setFont(QFont("Academy Engraved LET",38));
    title->setStyleSheet("color:blue");

    timer = new Timer(this);
    timer->move(670,110);

    startButton = new QPushButton("开始/暂停(&P)",this);
    startButton->setFocusPolicy(Qt::NoFocus);
    startButton->resize(211,61);
    startButton->move(680,190);
    startButton->setFont(QFont("楷体",18));
    connect(startButton,SIGNAL(clicked(bool)),timer,SLOT(changeState()));

    restartButton = new QPushButton("重新开始",this);
    restartButton->setFocusPolicy(Qt::NoFocus);
    restartButton->resize(211,61);
    restartButton->move(680,260);
    restartButton->setFont(QFont("楷体",18));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(stop()));
    connect(restartButton,SIGNAL(clicked(bool)),timer,SLOT(start()));
    connect(restartButton,SIGNAL(clicked(bool)),gameBoard,SLOT(restart()));

    exitButton = new QPushButton("主菜单",this);
    exitButton->setFocusPolicy(Qt::NoFocus);
    exitButton->resize(211,61);
    exitButton->move(680,330);
    exitButton->setFont(QFont("楷体",18));
    connect(exitButton,SIGNAL(clicked(bool)),this,SIGNAL(exitToMenu()));

    undoButton = new QPushButton("撤销(&U)",this);
    undoButton->setFocusPolicy(Qt::NoFocus);
    undoButton->resize(100,40);
    undoButton->move(680,460);
    undoButton->setFont(QFont("华文新魏",14));
    connect(undoButton,SIGNAL(clicked(bool)),undoAction,SLOT(trigger()));

    redoButton = new QPushButton("重做(&R)", this);
    redoButton->setFocusPolicy(Qt::NoFocus);
    redoButton->resize(100,40);
    redoButton->move(790,460);
    redoButton->setFont(QFont("华文新魏",14));
    connect(redoButton,SIGNAL(clicked(bool)),redoAction,SLOT(trigger()));

    markButton = new QPushButton("标记(&M)",this);
    markButton->setFocusPolicy(Qt::NoFocus);
    markButton->resize(100,40);
    markButton->move(680,410);
    markButton->setFont(QFont("华文新魏",14));
    connect(markButton,SIGNAL(clicked(bool)),gameBoard,SLOT(markFocusBlock()));

    deleteButton = new QPushButton("清除",this);
    deleteButton->setFocusPolicy(Qt::NoFocus);
    deleteButton->resize(100,40);
    deleteButton->move(790,410);
    deleteButton->setFont(QFont("华文新魏",14));
    connect(deleteButton,SIGNAL(clicked(bool)),gameBoard,SLOT(clearFocusBlock()));

    hintButton = new QPushButton("提示(&H)",this);
    hintButton->setFocusPolicy(Qt::NoFocus);
    hintButton->resize(100,40);
    hintButton->move(680,510);
    hintButton->setFont(QFont("华文新魏",14));

    solveButton = new QPushButton("答案",this);
    solveButton->setFocusPolicy(Qt::NoFocus);
    solveButton->resize(100,40);
    solveButton->move(790,510);
    solveButton->setFont(QFont("华文新魏",14));
    connect(solveButton,SIGNAL(clicked(bool)),this,SLOT(solve()));

    connect(gameBoard,SIGNAL(addNumberCommand(int*,int,NumberBlock*)),this,SLOT(addNumberCommand(int*,int,NumberBlock*)));
    connect(gameBoard,SIGNAL(deleteNumberCommand(int*,int,NumberBlock*)),this,SLOT(deleteNumberCommand(int*,int,NumberBlock*)));

    QSignalMapper* mapper= new QSignalMapper(this);
    for(int i=0;i<9;i++){
        numberButton[i] = new QPushButton(this);
        numberButton[i]->setFixedSize(40,40);
        QFont font(numberButton[i]->font());
        font.setPixelSize(30);
        numberButton[i]->setFont(QFont(font));
        numberButton[i]->move(590,30+i*60);
        numberButton[i]->setFocusPolicy(Qt::NoFocus);
        numberButton[i]->setText(QVariant(i+1).toString());
        numberButton[i]->setStyleSheet("border:none");
        numberButton[i]->setStyleSheet("background:rgb(0,225,255,50)");
        connect(numberButton[i],SIGNAL(clicked(bool)),mapper,SLOT(map()));
        mapper->setMapping(numberButton[i],i+1);
    }
    connect(mapper,SIGNAL(mapped(int)),gameBoard,SLOT(changeNumberOnFocusBlock(int)));

    setStyleSheet(".QPushButton{background:rgb(0,225,255,50)}");

    connect(gameBoard,SIGNAL(finish()),this,SIGNAL(finish()));
    connect(this,SIGNAL(setDatabase(Database*)),gameBoard,SLOT(setDatabase(Database*)));

}

void MainForm::addNumberCommand(int *numbers, int count, NumberBlock *block){
    undoStack->push(new AddNumbersCommand(numbers,count,block));
}

void MainForm::deleteNumberCommand(int *numbers, int count, NumberBlock *block){
    undoStack->push(new DeleteNumberCommand(numbers,count,block));
}

void MainForm::setLevel(int level){
    gameBoard->reset();
    state newState = sudokuAlgorithm.getSudoku(level);
    int *b = new int[81];
    bool *c = new bool[81];
    for(int i=0;i<81;i++){
        for(int j=0;j<9;j++){
            if(newState.number[i]==0){
                b[i] = 0;
                c[i] = 1;
            }
            else if(newState.number[i]==1){
                b[i]=j+1;
                c[i] = 0;
                break;
            }
            else
                newState.number[i]/=2;
        }
    }
    gameBoard->setNumbers(b);
    gameBoard->setEditable(c);
    setTitle("Level "+QVariant(level).toString());
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
    undoStack->clear();
}

void MainForm::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    //设置抗锯齿
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    p->setBrush(QColor(255,250,205,100));
    p->setPen(Qt::transparent);
    p->drawRect(rect());
    delete p;
}

void MainForm::setTitle(QString text){
    title->setText(text);
}

void MainForm::reset(){
    gameBoard->reset();
    undoStack->clear();
}

void MainForm::setGame(QString numbers, QString isEditable, int usedTime, int level){
    gameBoard->initializeGameBoard(numbers, isEditable, usedTime, level);
    setTitle("Level "+QVariant(level).toString());
    undoStack->clear();
    timer->start();
    timer->setTime(usedTime);
}
