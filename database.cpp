#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{
    connect();
}

QSqlDatabase* Database::database(){
    return &db;
}

bool Database::connect(QString name){
    //打开数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);
    if(!db.open()){
        qDebug()<<"Build database failed";
        return false;
    }
    else{
        qDebug()<<"Build database succeed";
        //判断表"Sudoku"是否存在
        QStringList tableList = db.tables();
        QSqlQuery query;
        if(!tableList.contains("Sudoku")){
            //如果不存在Sudoku表则创建
            qDebug()<<"Sudoku table not exist";
            if(!query.exec("CREATE TABLE Sudoku("
                           "Date varchar,"
                           "Name varchar,"
                           "Numbers varchar,"
                           "isEditable varchar,"
                           "UsedTime int,"
                           "Level int)")){
                qDebug()<<"Build table \"Sudoku\" failed";
            }
        }
    }


    return true;
}

bool Database::addData(QString name, QString numbers, QString isEditable, int usedTime, int level){
    QSqlQuery query(db);
    QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString addDataString = QString("INSERT INTO Sudoku(Date, Name, Numbers, isEditable, UsedTime, Level) VALUES ('%1', '%2', '%3', '%4', %5, %6)").
            arg(date).arg(name).arg(numbers).arg(isEditable).arg(usedTime).arg(level);
    qDebug()<<addDataString;
    if(!query.exec(addDataString)){
        qDebug()<<"Add data failed";
        return false;
    }
    return true;
}

QList<QList<QVariant>> Database::getData(QString name){
    QList<QList<QVariant>> result;
    QString selectString = QString("SELECT * FROM Sudoku WHERE Name = '%1'").arg(name);
    QSqlQuery query;
    query.exec(selectString);
    while(query.next()){
        QList<QVariant> list;
        for(int i=0;i<4;i++){
            list.append(query.value(i));
        }result.append(list);
    }return result;
}
