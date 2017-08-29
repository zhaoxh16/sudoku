#include "gameboard.h"

GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{
    setFixedSize(552, 552);
    //构建布局
    QGridLayout* layout = new QGridLayout;//总的layout
    layout->setMargin(3);
    layout->setSpacing(0);
    QVBoxLayout* vLayout = new QVBoxLayout;//棋盘layout
    vLayout->setSpacing(0);
    vLayout->setMargin(0);
    QHBoxLayout* layout1 = new QHBoxLayout;//第一行
    layout1->setSpacing(0);
    QHBoxLayout* layout2 = new QHBoxLayout;//第二行
    layout2->setSpacing(0);
    QHBoxLayout* layout3 = new QHBoxLayout;//第三行
    layout3->setSpacing(0);
    QGridLayout* blockLayout[9];
    for(int i=0;i<9;i++){
        blockLayout[i]= new QGridLayout;//九个九宫格从上到下012 345 678
    }

    //四个方向键信号映射器，负责numberblock和gameboard的映射
    QSignalMapper *upSignalMapper = new QSignalMapper(this);
    QSignalMapper *downSignalMapper = new QSignalMapper(this);
    QSignalMapper *leftSignalMapper = new QSignalMapper(this);
    QSignalMapper *rightSignalMapper = new QSignalMapper(this);

    //highlightframe信号映射器
    QSignalMapper *showHighlightSignalMapper = new QSignalMapper(this);

    //设置numberblocks
    int number = -1;
    for(int i=0;i<9;i++){//i表示行
        for(int j=0;j<9;j++){//j表示列
            ++number;
            blocks[number] = new NumberBlock(this);

            //分别添加到九个九宫格中
            if(i<3&&j<3)
                blockLayout[0]->addWidget(blocks[number],i,j);
            else if(i<3&&j<6)
                blockLayout[1]->addWidget(blocks[number],i,j);
            else if(i<3)
                blockLayout[2]->addWidget(blocks[number],i,j);
            else if(i<6&&j<3)
                blockLayout[3]->addWidget(blocks[number],i,j);
            else if(i<6&&j<6)
                blockLayout[4]->addWidget(blocks[number],i,j);
            else if(i<6)
                blockLayout[5]->addWidget(blocks[number],i,j);
            else if(j<3)
                blockLayout[6]->addWidget(blocks[number],i,j);
            else if(j<6)
                blockLayout[7]->addWidget(blocks[number],i,j);
            else
                blockLayout[8]->addWidget(blocks[number],i,j);

            //连接方向键信号映射器
            //为了区别上下左右，对映射器的数字分别加了0，100，200，300
            QObject::connect(blocks[number],SIGNAL(moveUp()),upSignalMapper,SLOT(map()));
            upSignalMapper->setMapping(blocks[number],number);
            QObject::connect(blocks[number],SIGNAL(moveDown()),downSignalMapper,SLOT(map()));
            downSignalMapper->setMapping(blocks[number],100+number);
            QObject::connect(blocks[number],SIGNAL(moveLeft()),leftSignalMapper,SLOT(map()));
            leftSignalMapper->setMapping(blocks[number],200+number);
            QObject::connect(blocks[number],SIGNAL(moveRight()),rightSignalMapper,SLOT(map()));
            rightSignalMapper->setMapping(blocks[number],300+number);

            //连接highlightframe信号映射器
            QObject::connect(blocks[number],SIGNAL(highlight(int)),showHighlightSignalMapper,SLOT(map()));
            showHighlightSignalMapper->setMapping(blocks[number],number);
            //连接数字高亮信号映射器
            QObject::connect(blocks[number],SIGNAL(highlight(int)),this,SLOT(showHighlightNumber(int)));
        }
    }

    //连接方向键的信号
    QObject::connect(upSignalMapper,SIGNAL(mapped(int)),this,SLOT(moveFocus(int)));
    QObject::connect(downSignalMapper,SIGNAL(mapped(int)),this,SLOT(moveFocus(int)));
    QObject::connect(leftSignalMapper,SIGNAL(mapped(int)),this,SLOT(moveFocus(int)));
    QObject::connect(rightSignalMapper,SIGNAL(mapped(int)),this,SLOT(moveFocus(int)));

    //连接highlight信号
    QObject::connect(showHighlightSignalMapper,SIGNAL(mapped(int)),this,SLOT(showHighlightFrame(int)));

    //构建布局
    layout1->addLayout(blockLayout[0]);
    layout1->addSpacing(3);
    layout1->addLayout(blockLayout[1]);
    layout1->addSpacing(3);
    layout1->addLayout(blockLayout[2]);
    layout2->addLayout(blockLayout[3]);
    layout2->addSpacing(3);
    layout2->addLayout(blockLayout[4]);
    layout2->addSpacing(3);
    layout2->addLayout(blockLayout[5]);
    layout3->addLayout(blockLayout[6]);
    layout3->addSpacing(3);
    layout3->addLayout(blockLayout[7]);
    layout3->addSpacing(3);
    layout3->addLayout(blockLayout[8]);

    vLayout->addLayout(layout1);
    vLayout->addSpacing(3);
    vLayout->addLayout(layout2);
    vLayout->addSpacing(3);
    vLayout->addLayout(layout3);

    layout->addLayout(vLayout,0,0,9,9);

    //设置highlightframe
    for(int i=0;i<9;i++){
        rowFrame[i]= new HighlightFrame(this);
        layout->addWidget(rowFrame[i],i,0,1,9);
        rowFrame[i]->setVisible(false);
        columnFrame[i] = new HighlightFrame(this);
        layout->addWidget(columnFrame[i],0,i,9,1);
        columnFrame[i]->setVisible(false);
    }

    //设置布局
    setLayout(layout);

    //temp 设置editable

    blocks[5]->setEditable(false);
    blocks[5]->setNumber(3);
    blocks[18]->setEditable(false);
    blocks[18]->setNumber(2);
    blocks[35]->setEditable(false);
    blocks[35]->setNumber(9);

}

void GameBoard::moveFocus(int number){//方向按键槽
    int flag = number / 100;//移动方向，0为上，1为下，2为左，3为右
    int newNumber = number % 100;
    if(flag==0){
        if(newNumber>=9)
            blocks[newNumber-9]->setFocus();
    }else if(flag==1){
        if(newNumber<72)
            blocks[newNumber+9]->setFocus();
    }else if(flag==2){
        if(newNumber%9!=0)
            blocks[newNumber-1]->setFocus();
    }else if(flag==3){
        if(newNumber%9!=8)
            blocks[newNumber+1]->setFocus();
    }

}

void GameBoard::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    //设置抗锯齿
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    p->setPen(QPen(Qt::red,5));
    p->drawRect(rect());
    p->setPen(QPen(Qt::blue,3));
    p->drawLine(QPoint(width()/3,5),QPoint(width()/3,height()-5));
    p->drawLine(QPoint(width()/3*2,5),QPoint(width()/3*2,height()-5));
    p->drawLine(QPoint(5,height()/3),QPoint(width()-5,height()/3));
    p->drawLine(QPoint(5,height()/3*2),QPoint(width()-5,height()/3*2));
    delete p;
}

void GameBoard::showHighlightFrame(int number){
    for(int i=0;i<9;i++){
        rowFrame[i]->setVisible(false);
        columnFrame[i]->setVisible(false);
    }
    rowFrame[number/9]->setVisible(true);
    columnFrame[number%9]->setVisible(true);
}

void GameBoard::showHighlightNumber(int number){
    for(int i=0;i<81;i++){
        if(blocks[i]->getNumber()==number)
            blocks[i]->highlightNumber();
        else
            blocks[i]->cancelHighlightNumber();
    }
}

void GameBoard::restart(){
    for(int i=0;i<81;i++){
        if(blocks[i]->isEditable()){
            blocks[i]->clear();
        }
    }
}
