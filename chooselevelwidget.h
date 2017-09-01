#ifndef CHOOSELEVELWIDGET_H
#define CHOOSELEVELWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>
#include <QPainter>

namespace Ui {
class ChooseLevelWidget;
}

class ChooseLevelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseLevelWidget(QWidget *parent = 0);
    ~ChooseLevelWidget();

signals:
    void chooseLevel(int level);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::ChooseLevelWidget *ui;
    QPushButton* pushButton[10];
};

#endif // CHOOSELEVELWIDGET_H
