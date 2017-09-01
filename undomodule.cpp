#include "undomodule.h"

AddNumbersCommand::AddNumbersCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Add Number"){
    this->numbers = new int[9];
    this->block = block;
    this->count = count;
    for(int i=0;i<9;i++){
        this->numbers[i] = numbers[i];
    }
    qDebug()<<"command: add number " + QVariant(numbers[0]).toString();
}

AddNumbersCommand::~AddNumbersCommand(){
    delete[] numbers;
}

void AddNumbersCommand::redo(){
    block->addNumbers(numbers,count);
    qDebug()<<"addNumberCommand redo active";
    qDebug()<<QVariant(numbers[0]).toString();
}

void AddNumbersCommand::undo(){
    block->deleteNumbers(numbers,count);
    qDebug()<<"addNumberCommand undo active";
    qDebug()<<QVariant(numbers[0]).toString();
}

DeleteNumberCommand::DeleteNumberCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Delete Number"){
    this->numbers = new int[9];
    this->block = block;
    this->count = count;
    for(int i=0;i<9;i++){
        this->numbers[i] = numbers[i];
    }
    qDebug()<<"command: delete number " + QVariant(numbers[0]).toString();
}

DeleteNumberCommand::~DeleteNumberCommand(){
    delete[] numbers;
}

void DeleteNumberCommand::redo(){
    block->deleteNumbers(numbers,count);
    qDebug()<<"deleteNumberCommand redo active";
    qDebug()<<QVariant(numbers[0]).toString();
}

void DeleteNumberCommand::undo(){
    block->addNumbers(numbers,count);
    qDebug()<<"deleteNumberCommand undo active";
    qDebug()<<QVariant(numbers[0]).toString();
}
