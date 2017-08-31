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
    void highlightPosition();
    void cancelHighlightPosition();
    int getNumber();
    int getOriginalNumber();
    bool isEditable();
    void clear(bool pushCommand = false);
    void addNumbers(int* numbers,int count, bool pushCommand = false);
    void deleteNumbers(int* numbers, int count, bool pushCommand = false);
    void changeNumberStatus(int number, bool pushCommand = false);
    void mark();
    void reset();

signals:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void highlight(int number);
    void addNumberCommand(int* numbers, int count, NumberBlock* thisBlock);//记录所添加的数字
    void deleteNumberCommand(int* numbers, int count, NumberBlock* thisBlock);//记录所删除的数字
    void judge();

public slots:


protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void changeBackgroundColor(QColor color);
    void changeLabelTextColor(QColor color);
    void changeSmallLabelTextColor(QColor color, int number = -1);

    QLabel* label;
    QLabel* smallLabel[9];
    int usedLabel = 0;

    bool editable = 1;
    bool marked = 0;
    bool isHighlightNumber = 0;
    bool isHighlightPosition = 0;
    bool focus = 0;
};

#endif // NUMBERBLOCK_H
