#include "undomodule.h"

AddNumbersCommand::AddNumbersCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Add Number"){
    this->numbers = new int[9];
    this->block = block;
    this->count = count;
    for(int i=0;i<9;i++){
        this->numbers[i] = numbers[i];
    }
}

AddNumbersCommand::~AddNumbersCommand(){
    delete[] numbers;
}

void AddNumbersCommand::redo(){
    block->addNumbers(numbers,count);
}

void AddNumbersCommand::undo(){
    block->deleteNumbers(numbers,count);
}

DeleteNumberCommand::DeleteNumberCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Delete Number"){
    this->numbers = new int[9];
    this->block = block;
    this->count = count;
    for(int i=0;i<9;i++){
        this->numbers[i] = numbers[i];
    }
}

DeleteNumberCommand::~DeleteNumberCommand(){
    delete[] numbers;
}

void DeleteNumberCommand::redo(){
    block->deleteNumbers(numbers,count);
}

void DeleteNumberCommand::undo(){
    block->addNumbers(numbers,count);
}
