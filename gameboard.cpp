#include "gameboard.h"

GameBoard::GameBoard(QWidget *parent) : QWidget(parent)
{
    //database=new Database;
    sudokuNumbers = new int[81];

    setFixedSize(540,540);
    //构建布局
    QGridLayout* layout = new QGridLayout(this);//总的layout
    layout->setMargin(0);
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
            //连接命令（用来撤销）信号
            QObject::connect(blocks[number],SIGNAL(addNumberCommand(int*,int,NumberBlock*)),this, SIGNAL(addNumberCommand(int*,int,NumberBlock*)));
            QObject::connect(blocks[number],SIGNAL(deleteNumberCommand(int*,int,NumberBlock*)),this,SIGNAL(deleteNumberCommand(int*,int,NumberBlock*)));
            //连接judge信号
            QObject::connect(blocks[number],SIGNAL(judge()),this,SLOT(judge()));

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
    layout1->addLayout(blockLayout[1]);
    layout1->addLayout(blockLayout[2]);
    layout2->addLayout(blockLayout[3]);
    layout2->addLayout(blockLayout[4]);
    layout2->addLayout(blockLayout[5]);
    layout3->addLayout(blockLayout[6]);
    layout3->addLayout(blockLayout[7]);
    layout3->addLayout(blockLayout[8]);

    vLayout->addLayout(layout1);
    vLayout->addLayout(layout2);
    vLayout->addLayout(layout3);

    layout->addLayout(vLayout,0,0,9,9);

    //添加BoardCover
    boardCover = new BoardCover(this);
    layout->addWidget(boardCover,0,0,9,9);

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
    /*
    blocks[5]->setEditable(false);
    blocks[5]->setNumber(3);
    blocks[18]->setEditable(false);
    blocks[18]->setNumber(2);
    blocks[35]->setEditable(false);
    blocks[35]->setNumber(9);
    */

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
    p->setPen(QPen(QColor(0,255,255,150),5));
    p->drawRect(rect());
    p->setPen(QPen(Qt::blue,3));
    p->drawLine(QPoint(width()/3,5),QPoint(width()/3,height()-5));
    p->drawLine(QPoint(width()/3*2,5),QPoint(width()/3*2,height()-5));
    p->drawLine(QPoint(5,height()/3),QPoint(width()-5,height()/3));
    p->drawLine(QPoint(5,height()/3*2),QPoint(width()-5,height()/3*2));
    delete p;
}

void GameBoard::showHighlightFrame(int number){
    int x = number%9;
    int y = number/9;

    for(int i=0;i<9;i++){
        rowFrame[i]->setVisible(false);
        columnFrame[i]->setVisible(false);
    }
    rowFrame[y]->setVisible(true);
    columnFrame[x]->setVisible(true);

    for(int i=0;i<81;i++){
        blocks[i]->cancelHighlightPosition();
    }
    y=y*9;
    for(int i=0;i<9;i++){
        blocks[x]->highlightPosition();
        x+=9;
        blocks[y]->highlightPosition();
        y+=1;
    }
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
            blocks[i]->cancelMark();
        }
    }
    boardCover->setCover(false);
}

void GameBoard::markFocusBlock(){
    NumberBlock* focusBlock;
    QWidget* currentItem = QApplication::focusWidget();
    if(currentItem!=NULL){
        if(currentItem->inherits("NumberBlock")){
            focusBlock = qobject_cast<NumberBlock*>(currentItem);
            focusBlock->mark();
        }
    }
}

void GameBoard::clearFocusBlock(){
    NumberBlock* focusBlock;
    QWidget* currentItem = QApplication::focusWidget();
    if(currentItem!=NULL){
        if(currentItem->inherits("NumberBlock")){
            focusBlock = qobject_cast<NumberBlock*>(currentItem);
            if(focusBlock->isEditable())
                focusBlock->clear();
        }
    }
}


void GameBoard::changeNumberOnFocusBlock(int number){
    NumberBlock* focusBlock;
    QWidget* currentItem = QApplication::focusWidget();
    if(currentItem!=NULL){
        if(currentItem->inherits("NumberBlock")){
            focusBlock = qobject_cast<NumberBlock*>(currentItem);
            focusBlock->changeNumberStatus(number);
        }
    }
}

void GameBoard::initializeGameBoard(int *numbers){
    for(int i=0;i<81;i++){
        if(numbers[i]==0)
            blocks[i]->setEditable(true);
        else{
            blocks[i]->setEditable(false);
            blocks[i]->setNumber(numbers[i]);
        }
    }
}

void GameBoard::judge(){//判断数独是否完成
    //判断每列是否都是对的
    bool allColumnRight = 1;
    for(int i=0;i<9;i++){//行
        bool columnRight = 1;
        bool exist[9];
        for(int j=0;j<9;j++){//初始化数组
            exist[j]=0;
        }
        for(int j=0;j<9;j++){//列
            int number = blocks[i*9+j]->getNumber();
            if(exist[number-1]){
                columnRight=0;
                break;
            }else
                exist[number-1]=1;
        }
        if(columnRight == 0){
            allColumnRight = 0;
            break;
        }
    }
    if(allColumnRight==0)
        return;

    //判断每行是否都是对的
    bool allRowRight = 1;
    for(int i=0;i<9;i++){//列
        bool rowRight = 1;
        bool exist[9];
        for(int j=0;j<9;j++){//初始化数组
            exist[j]=0;
        }
        for(int j=0;j<9;j++){//行
            int number = blocks[j*9+i]->getNumber();
            if(exist[number-1]){
                rowRight=0;
                break;
            }else
                exist[number-1]=1;
        }
        if(rowRight == 0){
            allRowRight = 0;
            break;
        }
    }
    if(allRowRight==0)
        return;

    //判断每个方格是否都是对的
    bool isRight = 1;
    for(int bigBlockNumber = 0;bigBlockNumber<9;bigBlockNumber++){
        bool flag = 1;
        int firstNumber = bigBlockNumber/3*27+bigBlockNumber%3*3;//该九宫格第一个格子的编号
        bool exist[9];
        for(int j=0;j<9;j++)
            exist[j] = 0;
        for(int i=0;i<9;i++){
            int changeNumber = i/3*9+i%3+firstNumber;
            //该格子是否能填该数字
            if(exist[blocks[changeNumber]->getNumber()-1]==1){
                flag = 0;
                break;
            }else
                exist[blocks[changeNumber]->getNumber()-1]=1;
        }
        if(flag ==0){
            isRight=0;
            break;
        }
    }
    if(isRight == 0)
        return;

    //如果上面都对了
    emit finish();

}

void GameBoard::reset(){
    for(int i=0;i<81;i++)
        blocks[i]->reset();
    for(int i=0;i<9;i++){
        rowFrame[i]->setVisible(false);
        rowFrame[i]->setVisible(false);
    }
    boardCover->setCover(false);
}

void GameBoard::setLevel(int level){
    QString levelName = "default_level_"+QVariant(level).toString();
    QList<QList<QVariant>> result = database->getData(levelName);
    QString numbers = result[0][2].toString();
    QString isEditable = result[0][3].toString();
    for(int i=0;i<81;i++){
        QString temp1 = "";
        QString temp2 = "";
        blocks[i]->setEditable(QVariant(temp1+isEditable.at(i)).toBool());
        if(numbers.at(i)=='0')
            continue;
        blocks[i]->setNumber(QVariant(temp2+numbers.at(i)).toInt());
    }
}

void GameBoard::initializeGameBoard(QString numbers, QString isEditable, int usedTime, int level){
    reset();
    for(int i=0;i<81;i++){
        QString temp1 = "";
        QString temp2 = "";
        blocks[i]->setEditable(QVariant(temp1+isEditable.at(i)).toBool());
        if(numbers.at(i)=='0')
            continue;
        blocks[i]->setNumber(QVariant(temp2+numbers.at(i)).toInt());
    }

}

int* GameBoard::getNumbers(){
    for(int i=0;i<81;i++){
        sudokuNumbers[i] = blocks[i]->getOriginalNumber();
    }
    return sudokuNumbers;
}

void GameBoard::setNumbers(int *numbers){
    for(int i=0;i<81;i++){
        blocks[i]->clear();
        if(numbers[i]!=0){
            blocks[i]->setNumber(numbers[i]);
        }
    }
}

void GameBoard::setEditable(bool *editable){
    for(int i=0;i<81;i++){
        blocks[i]->setEditable(editable[i]);
    }
}

void GameBoard::setDatabase(Database *database){
    this->database = database;
}

QString GameBoard::getSavedNumbers(){
    QString numbers = "";
    for(int i=0;i<81;i++){
        numbers+=QVariant(blocks[i]->getNumber()).toString();
    }
    return numbers;
}

QString GameBoard::getSavedEditable(){
    QString editables = "";
    for(int i=0;i<81;i++){
        editables+=QVariant(QVariant(blocks[i]->isEditable()).toInt()).toString();
    }
    return editables;
}

void GameBoard::cover(){
    boardCover->setCover(true);
}

void GameBoard::uncover(){
    boardCover->setCover(false);
}

void GameBoard::setSolutions(int *numbers){
    for(int i=0;i<81;i++){
        blocks[i]->getSolution(numbers[i]);
    }
}

void GameBoard::fillWithSolutions(){
    for(int i=0;i<81;i++){
        if(blocks[i]->isEditable()){
            blocks[i]->setSolution();
        }
    }
}

void GameBoard::hintFocusBlock(){
    NumberBlock* focusBlock;
    QWidget* currentItem = QApplication::focusWidget();
    if(currentItem!=NULL){
        if(currentItem->inherits("NumberBlock")){
            focusBlock = qobject_cast<NumberBlock*>(currentItem);
            if(focusBlock->isEditable())
                focusBlock->setSolution();
        }
    }
}
