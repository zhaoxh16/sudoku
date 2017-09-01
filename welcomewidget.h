#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QSound>

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
    void controlMusic();

protected:
    void paintEvent(QPaintEvent *event);

signals:
    void start();
    void load();
    void option();

private:
    Ui::WelcomeWidget *ui;
    QSound* bells;
};

#endif // WELCOMEWIDGET_H
