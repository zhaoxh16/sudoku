#ifndef UNDOMODULE_H
#define UNDOMODULE_H

#include <QUndoCommand>
#include "numberblock.h"

class AddNumbersCommand: public QUndoCommand{
public:
    AddNumbersCommand(int* numbers, int count, NumberBlock* block);

    virtual void redo();

    virtual void undo();

private:
    NumberBlock* block;
    int* numbers;
    int count;
};

class DeleteNumberCommand: public QUndoCommand{
public:
    DeleteNumberCommand(int* numbers, int count, NumberBlock* block);

    virtual void redo();

    virtual void undo();

private:
    NumberBlock* block;
    int* numbers;
    int count;
};

#endif // UNDOMODULE_H
