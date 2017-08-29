#include "numberblock.h"

NumberBlock::NumberBlock(QWidget *parent) : QWidget(parent){
    //设置block大小
    setFixedSize(60,60);
    //设置背景自动填充
    setAutoFillBackground(true);
    //设置focus策略
    setFocusPolicy(Qt::StrongFocus);

    //设置label
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(25);
    label->setFont(ft);
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(label,0,0,3,3);

    //设置smallLabel
    int number = -1;
    for(int i=0;i<3;i++)//row
        for(int j=0;j<3;j++){//column
            smallLabel[++number] = new QLabel(this);
            layout->addWidget(smallLabel[number],i,j,1,1);
            smallLabel[number]->setText("");
            smallLabel[number]->setAlignment(Qt::AlignCenter);
        }

    setLayout(layout);
}

void NumberBlock::focusInEvent(QFocusEvent *event){
    Q_UNUSED(event);
    //更改背景颜色
    if(editable){
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background, Qt::green);
        this->setPalette(palette);
    }

    //发送行列、数字高亮信号
    if(label->text()=="")//如果没有数字或有多个数字
        emit highlight(0);
    else//如果只填了一个数字
        emit highlight(QVariant(label->text()).toInt());

}

void NumberBlock::focusOutEvent(QFocusEvent *event){
    Q_UNUSED(event);
    //更改背景颜色
    if(editable){
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background, Qt::transparent);
        this->setPalette(palette);
    }
}

void NumberBlock::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    //设置抗锯齿
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    p->setBrush(Qt::transparent);
    p->setPen(QColor(0,255,255));
    p->drawRect(rect());
    delete p;
}

void NumberBlock::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    if(key!=Qt::Key_1&&key!=Qt::Key_2&&key!=Qt::Key_3&&key!=Qt::Key_4&&key!=Qt::Key_5&&key!=Qt::Key_6&&
            key!=Qt::Key_7&&key!=Qt::Key_8&&key!=Qt::Key_9&&key!=Qt::Key_Delete&&key!=Qt::Key_Backspace
            &&key != Qt::Key_Up&&key != Qt::Key_Down&&key != Qt::Key_Left&&key != Qt::Key_Right)//按键无效
        QWidget::keyPressEvent(event);
    else if(key == Qt::Key_Up||key == Qt::Key_Down||key == Qt::Key_Left||key == Qt::Key_Right){//按键为上下左右
        switch(key){
            case Qt::Key_Up:emit moveUp();break;
            case Qt::Key_Down:emit moveDown();break;
            case Qt::Key_Left:emit moveLeft();break;
            case Qt::Key_Right:emit moveRight();break;
        }
    }
    else if(editable){//可编辑的方格
        if(usedSmallLabel == 0){//该格子内没有任何数字
            if(key == Qt::Key_Delete||key == Qt::Key_Backspace)//按键为删除
                label->setText("");//清除数字
            else{//按键为数字
                usedSmallLabel = 1;//修改状态为该格子内有一个数字
                switch(key){
                    case Qt::Key_1:label->setText("1");break;
                    case Qt::Key_2:label->setText("2");break;
                    case Qt::Key_3:label->setText("3");break;
                    case Qt::Key_4:label->setText("4");break;
                    case Qt::Key_5:label->setText("5");break;
                    case Qt::Key_6:label->setText("6");break;
                    case Qt::Key_7:label->setText("7");break;
                    case Qt::Key_8:label->setText("8");break;
                    case Qt::Key_9:label->setText("9");break;
                }
            }
        }else if(usedSmallLabel == 1){//该格子内有一个数字
            if(key == Qt::Key_Delete||key == Qt::Key_Backspace){//按键为删除
                label->setText("");//清除数字
                usedSmallLabel = 0;//修改状态为该格子内没有数字
            }else{//按键为数字
                int temp = QVariant(label->text()).toInt();//label当前的text
                smallLabel[temp-1]->setText(QVariant(temp).toString());//设置smallLabel显示原来的那个数字
                label->setText("");//清除原来label内的数字
                switch(key){
                    case Qt::Key_1:smallLabel[0]->setText("1");break;
                    case Qt::Key_2:smallLabel[1]->setText("2");break;
                    case Qt::Key_3:smallLabel[2]->setText("3");break;
                    case Qt::Key_4:smallLabel[3]->setText("4");break;
                    case Qt::Key_5:smallLabel[4]->setText("5");break;
                    case Qt::Key_6:smallLabel[5]->setText("6");break;
                    case Qt::Key_7:smallLabel[6]->setText("7");break;
                    case Qt::Key_8:smallLabel[7]->setText("8");break;
                    case Qt::Key_9:smallLabel[8]->setText("9");break;
                }
                //计算现在格子内的数字数量
                int flag = 0;
                for(int i=0;i<9;i++){
                    if(smallLabel[i]->text()!="")
                        flag++;
                }
                //如果格子内只有一个数字则恢复原来的显示方式
                if(flag == 1){
                    for(int i=0;i<9;i++){
                        if(smallLabel[i]->text()!=""){
                            temp = QVariant(smallLabel[i]->text()).toInt();
                            label->setText(QVariant(temp).toString());
                            smallLabel[i]->setText("");
                        }
                    }
                }else
                    usedSmallLabel = 2;//改变状态为有多个小方格在用
            }
        }else{//格子内已有多个数字
            if(key == Qt::Key_Delete||key == Qt::Key_Backspace){//按键为删除
                for(int i=0;i<9;i++){//清除数字
                    smallLabel[i]->setText("");
                }
                usedSmallLabel = 0;//修改状态为该格子内没有数字
            }else{//按键为数字
                switch(key){
                    case Qt::Key_1:smallLabel[0]->setText("1");break;
                    case Qt::Key_2:smallLabel[1]->setText("2");break;
                    case Qt::Key_3:smallLabel[2]->setText("3");break;
                    case Qt::Key_4:smallLabel[3]->setText("4");break;
                    case Qt::Key_5:smallLabel[4]->setText("5");break;
                    case Qt::Key_6:smallLabel[5]->setText("6");break;
                    case Qt::Key_7:smallLabel[6]->setText("7");break;
                    case Qt::Key_8:smallLabel[7]->setText("8");break;
                    case Qt::Key_9:smallLabel[8]->setText("9");break;
                }
            }

        }
    }else{//不可编辑的方格
        QWidget::keyPressEvent(event);
    }
}

void NumberBlock::setEditable(bool editable){
    this->editable=editable;
    if(!editable){
        QPalette palette = this->palette();
        palette.setColor(QPalette::Background, Qt::yellow);
        this->setPalette(palette);
    }
}

void NumberBlock::setNumber(int number){
    label->setText(QVariant(number).toString());
}

int NumberBlock::getNumber(){
    return QVariant(label->text()).toInt();
}

void NumberBlock::highlightNumber(){
    QFont ft = label->font();
    ft.setBold(true);
    label->setFont(ft);
    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText,Qt::red);
    label->setPalette(palette);
}

void NumberBlock::cancelHighlightNumber(){
    QFont ft = label->font();
    ft.setBold(false);
    label->setFont(ft);
    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText,Qt::black);
    label->setPalette(palette);
}
