#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeWidget(QWidget *parent = 0);
    ~WelcomeWidget();

public slots:
    void exitGame();

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void start();
    void load();
    void option();

private:
    Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
