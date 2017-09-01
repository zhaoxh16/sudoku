#include "loadwidget.h"
#include "ui_loadwidget.h"

LoadWidget::LoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadWidget)
{
    ui->setupUi(this);
    dataView = ui->tableView;
    //dataView->setFixedSize(260,240);
    //dataView->move(50,150);
    dataView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dataView->setSelectionBehavior(QAbstractItemView::SelectRows);
    dataView->setSelectionMode(QAbstractItemView::SingleSelection);
    setStyleSheet(".QPushButton{background:rgb(0,225,255,50)}");

    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SIGNAL(returnToMenu()));
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(loadData()));
}

void LoadWidget::setDatabase(Database *database){
    this->database = database;
    dataModel = new QSqlTableModel(this,*database->database());
}

void LoadWidget::refreshData(){
    dataModel->setTable("Sudoku");
    dataModel->select();
    dataView->setModel(dataModel);
}

LoadWidget::~LoadWidget()
{
    delete ui;
}

void LoadWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    p->setBrush(QColor(255,250,205,100));
    p->setPen(Qt::transparent);
    p->drawRect(rect());
    delete p;
}

void LoadWidget::loadData(){
    int row = dataView->currentIndex().row();
    if(row!=-1){
        QString numbers = dataModel->data(dataModel->index(row,2)).toString();
        QString isEditable = dataModel->data(dataModel->index(row,3)).toString();
        int usedTime = dataModel->data(dataModel->index(row,4)).toInt();
        int level = dataModel->data(dataModel->index(row,5)).toInt();
        emit setGame(numbers, isEditable, usedTime, level);
    }
}
