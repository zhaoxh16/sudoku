#include "undomodule.h"

AddNumbersCommand::AddNumbersCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Add Number"){
    this->block = block;
    this->numbers = numbers;
    this->count = count;
}

void AddNumbersCommand::redo(){
    block->addNumbers(numbers,count,false);
}

void AddNumbersCommand::undo(){
    block->deleteNumbers(numbers,count,false);
}

DeleteNumberCommand::DeleteNumberCommand(int* numbers, int count, NumberBlock* block):QUndoCommand("Delete Number"){
    this->block = block;
    this->numbers = numbers;
    this->count = count;
}

void DeleteNumberCommand::redo(){
    block->deleteNumbers(numbers,count,false);
}

void DeleteNumberCommand::undo(){
    block->addNumbers(numbers,count,false);
}
