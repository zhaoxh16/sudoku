#include "loadwidget.h"
#include "ui_loadwidget.h"

LoadWidget::LoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadWidget)
{
    ui->setupUi(this);
    dataView = new QTableView;
    dataView->setFixedSize(260,240);
    dataView->move(50,150);
    dataView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setStyleSheet(".QPushButton{background:rgb(0,225,255,50)}");

    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SIGNAL(returnToMenu()));
}

void LoadWidget::setDatabase(Database *database){
    this->database = database;
}

void LoadWidget::refreshData(){
    if(!dataModel)
        dataModel = new QSqlTableModel(this,*database->database());
    dataModel->setTable("Sudoku");
    dataModel->select();
    dataView->setModel(dataModel);
}

LoadWidget::~LoadWidget()
{
    delete ui;
}
