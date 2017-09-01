#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chooseLevelWidget = new ChooseLevelWidget(this);
    setCentralWidget(chooseLevelWidget);
    connect(chooseLevelWidget,SIGNAL(chooseLevel(int)),this,SLOT(setLevel(int)));
    setFixedSize(chooseLevelWidget->width(),chooseLevelWidget->height());
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    database = new Database;
}

MainWindow::~MainWindow()
{

}

void MainWindow::setLevel(int level){
    mainform = new MainForm(this);
    connect(mainform,SIGNAL(finish()),this,SLOT(returnToMenu()));
    connect(mainform,SIGNAL(exitToMenu()),this,SLOT(returnToMenu()));
    setCentralWidget(mainform);
    setFixedSize(mainform->width(),mainform->height());
    connect(this,SIGNAL(setDatabase(Database*)),mainform,SIGNAL(setDatabase(Database*)));
    emit setDatabase(database);
    mainform->setLevel(level);
}

void MainWindow::returnToMenu(){
    chooseLevelWidget = new ChooseLevelWidget(this);
    connect(chooseLevelWidget,SIGNAL(chooseLevel(int)),this,SLOT(setLevel(int)));
    setCentralWidget(chooseLevelWidget);
    setFixedSize(chooseLevelWidget->width(),chooseLevelWidget->height());
}
