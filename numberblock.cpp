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

    //设置字体
    changeLabelTextColor(QColor(205,133,63));
    changeSmallLabelTextColor(QColor(205,133,63));

    setLayout(layout);
}

void NumberBlock::focusInEvent(QFocusEvent *event){
    Q_UNUSED(event);
    //更改背景颜色
    if(editable){
        changeBackgroundColor(Qt::green);
    }

    //发送行列、数字高亮信号
    if(label->text()=="")//如果没有数字或有多个数字
        emit highlight(-1);
    else//如果只填了一个数字
        emit highlight(QVariant(label->text()).toInt());

}

void NumberBlock::focusOutEvent(QFocusEvent *event){
    Q_UNUSED(event);
    //更改背景颜色
    if(editable){
        changeBackgroundColor(QColor(135,206,250));
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
    else if(key == Qt::Key_Up||key == Qt::Key_Down||key == Qt::Key_Left||key == Qt::Key_Right){
        switch(key){
            case Qt::Key_Up:emit moveUp();break;
            case Qt::Key_Down:emit moveDown();break;
            case Qt::Key_Left:emit moveLeft();break;
            case Qt::Key_Right:emit moveRight();break;
        }
    }
    else{
        if(editable){//方格可编辑
            int *numbers = new int[9];
            switch(key){
            case Qt::Key_1:numbers[0]=1;addNumbers(numbers,1,true);break;
            case Qt::Key_2:numbers[0]=2;addNumbers(numbers,1,true);break;
            case Qt::Key_3:numbers[0]=3;addNumbers(numbers,1,true);break;
            case Qt::Key_4:numbers[0]=4;addNumbers(numbers,1,true);break;
            case Qt::Key_5:numbers[0]=5;addNumbers(numbers,1,true);break;
            case Qt::Key_6:numbers[0]=6;addNumbers(numbers,1,true);break;
            case Qt::Key_7:numbers[0]=7;addNumbers(numbers,1,true);break;
            case Qt::Key_8:numbers[0]=8;addNumbers(numbers,1,true);break;
            case Qt::Key_9:numbers[0]=9;addNumbers(numbers,1,true);break;
            case Qt::Key_Delete:
            case Qt::Key_Backspace:
                clear(true);break;

            }
        }
        else{//不可编辑的方格
            QWidget::keyPressEvent(event);
        }
    }
}

void NumberBlock::setEditable(bool editable){
    this->editable=editable;
    if(!editable){
        changeLabelTextColor(Qt::black);
    }else
        changeLabelTextColor(QColor(0,191,255));
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
    changeBackgroundColor(Qt::yellow);
}

void NumberBlock::cancelHighlightNumber(){
    QFont ft = label->font();
    ft.setBold(false);
    label->setFont(ft);
    changeBackgroundColor(QColor(135,206,250));
}

bool NumberBlock::isEditable(){
    return editable;
}

void NumberBlock::clear(bool pushCommand){
    int *numbers = new int[9];
    int count = 0;
    if(usedLabel == 0)
        return;
    else if(usedLabel == 1){
        numbers[0] = QVariant(label->text()).toInt();
        count = 1;
        deleteNumbers(numbers,count,pushCommand);
    }else{
        for(int i=0;i<9;i++){
            if(smallLabel[i]->text()!=""){
                numbers[count] = QVariant(smallLabel[i]->text()).toInt();
                ++count;
            }
        }
        deleteNumbers(numbers,count,pushCommand);
    }
}

void NumberBlock::addNumbers(int* numbers, int count, bool pushCommand){
    //发送command
    if(pushCommand){//如果pushCommand为真，那么count必定为1
        if(QVariant(numbers[0]).toString()!=label->text()&&
                QVariant(numbers[0]).toString()!=smallLabel[numbers[0]-1]->text())//如果之前没有这个数字
        emit addNumberCommand(numbers,count,this);
        else//已经有了就别费工夫了
            return;
    }

    //对方格进行操作
    if(usedLabel==0){//如果方格内一开始没有数字
        if(count==1){//最终方格内有一个数字
            label->setText(QVariant(numbers[0]).toString());
            usedLabel=1;
        }
        else{//最终方格内有多个数字
            for(int i=0;i<count;i++){
                smallLabel[numbers[i]-1]->setText(QVariant(numbers[i]).toString());
            }usedLabel=2;
        }
    }else if(usedLabel == 1&&count ==1&&numbers[0]==QVariant(label->text()).toInt())//如果方格内只有一个数字且和添加的唯一的数字相同
        return;
    else{//方格内最终会有多个数字
        if(label->text()!=""){
            smallLabel[QVariant(label->text()).toInt()-1]->setText(label->text());
            label->setText("");
        }for(int i=0;i<count;i++){
            smallLabel[numbers[i]-1]->setText(QVariant(numbers[i]).toString());
        }usedLabel=2;
    }

    //控制highlight
    for(int i=0;i<count;i++){
        emit highlight(numbers[i]);
    }
}

void NumberBlock::deleteNumbers(int* numbers, int count, bool pushCommand){
    if(usedLabel == 1){
        label->setText("");
        usedLabel = 0;
    }else{
        for(int i=0;i<count;i++){//更改label
            smallLabel[numbers[i]-1]->setText("");
        }
        int count2 = 0;//剩下的数字数量
        int leftNumber;//如果只剩一个时剩下的数字
        for(int i=0;i<9;i++){//统计数量
            if(smallLabel[i]->text()!=""){
                leftNumber = i+1;
                count2++;
            }
        }
        if(count2 == 0) usedLabel = 0;
        else if(count2 == 1){
            smallLabel[leftNumber-1]->setText("");
            label->setText(QVariant(leftNumber).toString());
            usedLabel = 1;
        }
    }
    if(pushCommand)
        emit deleteNumberCommand(numbers,count,this);
}

void NumberBlock::mark(){
    if(marked == 0){
        changeLabelTextColor(Qt::red);
        changeSmallLabelTextColor(Qt::red);
        marked = 1;
    }else{
        if(editable){
            changeLabelTextColor(QColor(205,133,63));
            changeSmallLabelTextColor(QColor(205,133,63));
        }else{
            changeLabelTextColor(Qt::black);
            changeSmallLabelTextColor(Qt::black);
        }
        marked = 0;
    }
}

void NumberBlock::changeBackgroundColor(QColor color){
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, color);
    this->setPalette(palette);
}

void NumberBlock::changeLabelTextColor(QColor color){
    QPalette palette = label->palette();
    palette.setColor(QPalette::WindowText,color);
    label->setPalette(palette);
}

void NumberBlock::changeSmallLabelTextColor(QColor color, int number){
    QPalette palette = smallLabel[0]->palette();
    palette.setColor(QPalette::WindowText,color);
    if(number == -1)
        for(int i=0;i<9;i++)
            smallLabel[i]->setPalette(palette);
    else
        smallLabel[number]->setPalette(palette);

}

