#ifndef SUDOKUALGORITHM_H
#define SUDOKUALGORITHM_H

#include <QObject>

class SudokuAlgorithm : public QObject
{
    Q_OBJECT
public:
    explicit SudokuAlgorithm(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SUDOKUALGORITHM_H