#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "mainform.h"
#include "chooselevelwidget.h"
#include "welcomewidget.h"
#include "loadwidget.h"
#include "windialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setLevel(int level);
    void returnToMenu();
    void chooseLevel();
    void load();
    void setGame(QString numbers, QString isEditable, int usedTime, int level);
    void win();

signals:
    void setDatabase(Database* database);

private:
    MainForm* mainform;
    ChooseLevelWidget* chooseLevelWidget;
    WelcomeWidget* welcomeWidget;
    Database* database;
    QStackedWidget* stackWidget;
    LoadWidget* loadWidget;
    WinDialog* dialog = NULL;
};

#endif // MAINWINDOW_H
