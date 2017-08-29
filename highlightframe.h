#ifndef HIGHLIGHTFRAME_H
#define HIGHLIGHTFRAME_H

#include <QWidget>
#include <QPainter>

class HighlightFrame : public QWidget
{
    Q_OBJECT
public:
    explicit HighlightFrame(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // HIGHLIGHTFRAME_H
