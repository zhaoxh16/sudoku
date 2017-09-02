#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    stackWidget = new QStackedWidget(this);
    setCentralWidget(stackWidget);
    stackWidget->setFixedSize(360,480);

    welcomeWidget = new WelcomeWidget(this);
    connect(welcomeWidget,SIGNAL(start()),this,SLOT(chooseLevel()));
    connect(welcomeWidget,SIGNAL(load()),this,SLOT(load()));
    stackWidget->addWidget(welcomeWidget);

    chooseLevelWidget = new ChooseLevelWidget(this);
    connect(chooseLevelWidget,SIGNAL(chooseLevel(int)),this,SLOT(setLevel(int)));
    stackWidget->addWidget(chooseLevelWidget);

    loadWidget = new LoadWidget(this);
    connect(loadWidget,SIGNAL(returnToMenu()),this,SLOT(returnToMenu()));
    connect(this,SIGNAL(setDatabase(Database*)),loadWidget,SLOT(setDatabase(Database*)));
    connect(loadWidget,SIGNAL(setGame(QString,QString,int,int)),this,SLOT(setGame(QString,QString,int,int)));
    stackWidget->addWidget(loadWidget);

    mainform = new MainForm(this);
    connect(mainform,SIGNAL(exitToMenu()),this,SLOT(returnToMenu()));
    connect(this,SIGNAL(setDatabase(Database*)),mainform,SIGNAL(setDatabase(Database*)));
    connect(mainform,SIGNAL(youWin()),this,SLOT(win()));
    stackWidget->addWidget(mainform);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    database = new Database;
    emit setDatabase(database);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setLevel(int level){
    stackWidget->setCurrentWidget(mainform);
    mainform->setLevel(level);
    stackWidget->setFixedSize(940,580);
    setFixedSize(940,580);
    /*
    mainform = new MainForm(this);
    connect(mainform,SIGNAL(finish()),this,SLOT(returnToMenu()));
    connect(mainform,SIGNAL(exitToMenu()),this,SLOT(returnToMenu()));
    setCentralWidget(mainform);
    setFixedSize(mainform->width(),mainform->height());
    connect(this,SIGNAL(setDatabase(Database*)),mainform,SIGNAL(setDatabase(Database*)));
    emit setDatabase(database);
    mainform->setLevel(level);
    */
}

void MainWindow::returnToMenu(){
    stackWidget->setCurrentWidget(welcomeWidget);
    stackWidget->setFixedSize(360,480);
    setFixedSize(360,480);
    /*
    welcomeWidget = new WelcomeWidget(this);
    setCentralWidget(welcomeWidget);
    setFixedSize(welcomeWidget->width(),welcomeWidget->height());
    connect(welcomeWidget,SIGNAL(start()),this,SLOT(chooseLevel()));
    */
}

void MainWindow::chooseLevel(){
    stackWidget->setCurrentWidget(chooseLevelWidget);
    stackWidget->setFixedSize(360,480);
    setFixedSize(360,480);
//    chooseLevelWidget = new ChooseLevelWidget(this);
//    connect(chooseLevelWidget,SIGNAL(chooseLevel(int)),this,SLOT(setLevel(int)));
//    setCentralWidget(chooseLevelWidget);
//    setFixedSize(chooseLevelWidget->width(),chooseLevelWidget->height());
}

void MainWindow::load(){
    stackWidget->setCurrentWidget(loadWidget);
    stackWidget->setFixedSize(360,480);
    loadWidget->refreshData();
    setFixedSize(360,480);
}

void MainWindow::setGame(QString numbers, QString isEditable, int usedTime, int level){
    mainform->setGame(numbers,isEditable,usedTime,level);
    stackWidget->setCurrentWidget(mainform);
    stackWidget->setFixedSize(940,580);
    setFixedSize(940,580);
}

void MainWindow::win(){
    if(dialog == NULL){
        dialog = new WinDialog;
        dialog->setModal(true);
        dialog->move(this->width()/2,this->height()/2);
    }
    dialog->show();
}
