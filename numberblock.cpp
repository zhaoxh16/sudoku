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
    layout->setMargin(3);
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
    focus = 1;
    update();

    //发送行列、数字高亮信号
    if(label->text()=="")//如果没有数字或有多个数字
        emit highlight(-1);
    else//如果只填了一个数字
        emit highlight(QVariant(label->text()).toInt());

}

void NumberBlock::focusOutEvent(QFocusEvent *event){
    Q_UNUSED(event);
    //更改背景颜色
    focus = 0;
    update();
}

void NumberBlock::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);

    QPainter* p = new QPainter(this);
    //设置抗锯齿
    p->setRenderHint(QPainter::Antialiasing, true);
    //设置画刷颜色
    p->setBrush(QColor(0,245,255,10));
    p->setPen(Qt::transparent);

    if(editable){
        changeLabelTextColor(QColor(0,0,255,100));
        changeSmallLabelTextColor(QColor(0,0,255,100));
    }else{
        changeLabelTextColor(Qt::black);
        changeSmallLabelTextColor(Qt::black);
    }

    if(isHighlightPosition)
        p->setBrush(QColor(0,245,255,20));

    if(isHighlightNumber)
        p->setBrush(QColor(0,255,0,50));

    if(focus)
        p->setBrush(QColor(0,255,0,50));

    if(marked){
        p->setBrush(QColor(160,32,240,80));
    }

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
            switch(key){
            case Qt::Key_1:changeNumberStatus(1);break;
            case Qt::Key_2:changeNumberStatus(2);break;
            case Qt::Key_3:changeNumberStatus(3);break;
            case Qt::Key_4:changeNumberStatus(4);break;
            case Qt::Key_5:changeNumberStatus(5);break;
            case Qt::Key_6:changeNumberStatus(6);break;
            case Qt::Key_7:changeNumberStatus(7);break;
            case Qt::Key_8:changeNumberStatus(8);break;
            case Qt::Key_9:changeNumberStatus(9);break;
            case Qt::Key_Delete:
            case Qt::Key_Backspace:
                clear();break;

            }
        }
        else{//不可编辑的方格
            QWidget::keyPressEvent(event);
        }
    }
}

void NumberBlock::setEditable(bool editable){
    this->editable=editable;
    update();
}

void NumberBlock::setNumber(int number){
    label->setText(QVariant(number).toString());
    usedLabel = 1;
}

int NumberBlock::getNumber(){
    if(label->text()=="")
        return 0;
    else
        return QVariant(label->text()).toInt();
}

int NumberBlock::getOriginalNumber(){
    if(editable){
        return 0;
    }else
        return getNumber();
}

void NumberBlock::highlightNumber(){
    isHighlightNumber = 1;
    update();
}

void NumberBlock::cancelHighlightNumber(){
    isHighlightNumber = 0;
    update();
}

bool NumberBlock::isEditable(){
    return editable;
}

void NumberBlock::clear(){
    int *numbers = new int[9];
    int count = 0;
    if(usedLabel == 0)
        return;
    else if(usedLabel == 1){
        numbers[0] = QVariant(label->text()).toInt();
        count = 1;
        emit deleteNumberCommand(numbers,count,this);
    }else{
        for(int i=0;i<9;i++){
            if(smallLabel[i]->text()!=""){
                numbers[count] = QVariant(smallLabel[i]->text()).toInt();
                ++count;
            }
        }
        emit deleteNumberCommand(numbers,count,this);
    }
}

void NumberBlock::addNumbers(int* numbers, int count){

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

    //判断是否已经把数独填完
    emit judge();
}

void NumberBlock::deleteNumbers(int* numbers, int count){
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
}

void NumberBlock::mark(){
    if(marked == 0)
        marked = 1;
    else
        marked = 0;
    update();
}

void NumberBlock::highlightPosition(){
    isHighlightPosition = 1;
    update();
}

void NumberBlock::cancelHighlightPosition(){
    isHighlightPosition = 0;
    update();
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

void NumberBlock::reset(){
    clear();
    usedLabel = 0;
    editable = 1;
    marked = 0;
    isHighlightNumber = 0;
    isHighlightPosition = 0;
    focus = 0;
    update();
}


void NumberBlock::changeNumberStatus(int number){
    if(editable){
        int numbers[1];
        numbers[0] = number;
        if(QVariant(label->text()).toInt() == number || smallLabel[number-1]->text() != ""){
            emit deleteNumberCommand(numbers,1,this);
        }else
            emit addNumberCommand(numbers,1,this);
    }
}

void NumberBlock::cancelMark(){
    marked = 0;
    update();
}
