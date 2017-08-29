#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    MainForm* mainform = new MainForm(this);
    setCentralWidget(mainform);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
}

MainWindow::~MainWindow()
{

}
