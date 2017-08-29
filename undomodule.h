#ifndef UNDOMODULE_H
#define UNDOMODULE_H

#include <QUndoCommand>
#include "numberblock.h"

class AddNumbersCommand: public QUndoCommand{
public:
    AddNumbersCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Add Number"){
        this->block = block;
        this->numbers = numbers;
        this->count = count;
    }

    virtual void redo(){
        block->addNumbers(numbers,count);
    }

    virtual void undo(){
        block->deleteNumbers(numbers,count);
    }

private:
    NumberBlock* block;
    int* numbers;
    int count;
};

class DeleteNumberCommand: public QUndoCommand{
public:
    DeleteNumberCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Delete Number"){
        this->block = block;
        this->numbers = numbers;
        this->count = count;
    }

    virtual void redo(){
        block->deleteNumbers(numbers,count);
    }

    virtual void undo(){
        block->addNumbers(numbers,count);
    }

private:
    NumberBlock* block;
    int* numbers;
    int count;
};

#endif // UNDOMODULE_H
