#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QWidget>
#include <QTableVIew>
#include <QSqlTableModel>
#include "database.h"
#include <QPainter>

namespace Ui {
class LoadWidget;
}

class LoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadWidget(QWidget *parent = 0);
    ~LoadWidget();
    void setData();
    void refreshData();

public slots:
    void setDatabase(Database* database);
    void loadData();

signals:
    void returnToMenu();
    void setGame(QString numbers, QString isEditable, int usedTime, int level);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::LoadWidget *ui;
    Database* database;
    QTableView* dataView;
    QSqlTableModel* dataModel;
};

#endif // LOADWIDGET_H
