#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    chooseLevelWidget = new ChooseLevelWidget(this);
    setCentralWidget(chooseLevelWidget);
    connect(chooseLevelWidget,SIGNAL(chooseLevel(int)),this,SLOT(setLevel(int)));
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setLevel(int level){
    mainform = new MainForm(this);
    connect(mainform,SIGNAL(finish()),this,SLOT(returnToMenu()));
    connect(mainform,SIGNAL(exitToMenu()),this,SLOT(returnToMenu()));
    setCentralWidget(mainform);
    mainform->setLevel(level);
}

void MainWindow::returnToMenu(){
    chooseLevelWidget = new ChooseLevelWidget(this);
    connect(chooseLevelWidget,SIGNAL(chooseLevel(int)),this,SLOT(setLevel(int)));
    setCentralWidget(chooseLevelWidget);
}
