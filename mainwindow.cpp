#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainform = new MainForm(this);
    chooseLevelWidget = new ChooseLevelWidget(this);
    setCentralWidget(chooseLevelWidget);
    mainform->hide();
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);

    connect(chooseLevelWidget,SIGNAL(chooseLevel(int)),this,SLOT(setLevel(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::setLevel(int level){
    mainform->show();
    chooseLevelWidget->hide();
    setCentralWidget(mainform);
    mainform->setLevel(level);
}
