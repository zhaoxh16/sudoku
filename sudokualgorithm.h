#ifndef SUDOKUALGORITHM_H
#define SUDOKUALGORITHM_H

#include <stack>

struct status{
    int number[81];
};

class sudokuAlgorithm
{
public:
    sudokuAlgorithm();

private:
    std::stack<status> statusStack;

};

#endif // SUDOKUALGORITHM_H
