#ifndef CHOOSELEVELWIDGET_H
#define CHOOSELEVELWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>

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

private:
    Ui::ChooseLevelWidget *ui;
    QPushButton* pushButton[12];
};

#endif // CHOOSELEVELWIDGET_H
