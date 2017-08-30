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
                           "Id int,"
                           "Name varchar,"
                           "Numbers varchar,"
                           "isEditable varchar)")){
                qDebug()<<"Build table \"Sudoku\" failed";
            }
        }
    }


    return true;
}

bool Database::addData(QString name, QString numbers, QString isEditable){
    QSqlQuery query(db);
    QString addDataString = QString("INSERT INTO Sudoku(Id, Name, Numbers, isEditable) VALUES (1, '%1', '%2', '%3')").
            arg(name).arg(numbers).arg(isEditable);
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
