#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QList>
#include <QVariant>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    QSqlDatabase* database();
    bool connect(QString name = "sudoku.db");//连接数据库
    bool addData(QString name,QString numbers, QString isEditable);
    QList<QList<QVariant>> getData(QString name);

signals:

public slots:

private slots:

private:
    QSqlDatabase db;//数据库

};

#endif // DATABASE_H
