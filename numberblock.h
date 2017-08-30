#ifndef NUMBERBLOCK_H
#define NUMBERBLOCK_H

#include <QWidget>
#include <QPalette>
#include <QLineEdit>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QVariant>

class NumberBlock : public QWidget
{
    Q_OBJECT
public:
    explicit NumberBlock(QWidget *parent = nullptr);
    void setEditable(bool editable);
    void setNumber(int number);
    void highlightNumber();
    void cancelHighlightNumber();
    int getNumber();
    bool isEditable();
    void clear();
    void addNumbers(int* numbers,int count, bool pushCommand);
    void deleteNumbers(int* numbers, int count, bool pushCommand);
    void mark();

signals:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void highlight(int number);
    void addNumberCommand(int* numbers, int count, NumberBlock* thisBlock);//记录所添加的数字
    void deleteNumberCommand(int* numbers, int count, NumberBlock* thisBlock);//记录所删除的数字

public slots:


protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    QLabel* label;
    QLabel* smallLabel[9];
    bool editable = 1;
    int usedLabel = 0;
};

#endif // NUMBERBLOCK_H
