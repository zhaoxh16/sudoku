#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainform.h"
#include "chooselevelwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setLevel(int level);
    void returnToMenu();

signals:
    void setDatabase(Database* database);

private:
    MainForm* mainform;
    ChooseLevelWidget* chooseLevelWidget;
    Database* database;
};

#endif // MAINWINDOW_H
