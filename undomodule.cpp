#include "undomodule.h"

AddNumbersCommand::AddNumbersCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Add Number"){
    this->block = block;
    this->numbers = numbers;
    this->count = count;
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
    this->block = block;
    this->numbers = numbers;
    this->count = count;
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
