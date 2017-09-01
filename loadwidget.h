#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QWidget>
#include <QTableVIew>
#include <QSqlTableModel>
#include "database.h"

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

signals:
    void returnToMenu();

private:
    Ui::LoadWidget *ui;
    Database* database;
    QTableView* dataView;
    QSqlTableModel* dataModel;
};

#endif // LOADWIDGET_H
