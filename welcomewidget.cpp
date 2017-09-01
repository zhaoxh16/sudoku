#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    bells = new QSound("123.wav",this);
    bells->setLoops(QSound::Infinite);
    bells->play();

    setStyleSheet(".QPushButton{background:rgb(106,90,205,100)}");
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SIGNAL(start()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SIGNAL(load()));
    connect(ui->pushButton_4,SIGNAL(clicked(bool)),this,SLOT(exitGame()));
    connect(ui->pushButton_3,SIGNAL(clicked(bool)),this,SLOT(controlMusic()));
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    p->setBrush(QColor(255,250,205,100));
    p->setPen(Qt::transparent);
    p->drawRect(rect());
    delete p;
}

void WelcomeWidget::exitGame(){
    qApp->quit();
}

void WelcomeWidget::controlMusic(){
    if(ui->pushButton_3->text()=="音乐：开"){
        ui->pushButton_3->setText("音乐：关");
        bells->stop();
    }else{
        ui->pushButton_3->setText("音乐：开");
        bells->play();
    }
}
