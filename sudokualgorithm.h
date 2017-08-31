#ifndef SUDOKUALGORITHM_H
#define SUDOKUALGORITHM_H

#include <stack>

struct state{
    int number[81];//每个方格中可填的数字（二进制表示）
    int solutionNumber[81];//每个方格中可填数字的数量
    int blank;
};

class SudokuAlgorithm
{
public:
    SudokuAlgorithm();
    state solve(state initialState);

private:
    std::stack<state> stateStack;
    //isIn为true：要把number填入blockNumber格子；为false：number禁止填入blockNumber格子
    state changeState(state initialState, int blockNumber, int number, bool isIn);
    //求出某个二进制数的最靠后的为1的位
    int getFirstSolution(int number);


};

#endif // SUDOKUALGORITHM_H
