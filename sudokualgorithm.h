#ifndef SUDOKUALGORITHM_H
#define SUDOKUALGORITHM_H

#include <stack>
#include <vector>
#include <ctime>
#include <cstdlib>

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
    state initializeState(int* number);
    int getSolutionNumber(state initialState);//返回0为无解，1为唯一解，2为多解
    void reset();//清空stack

    state getCompleteSudoku();//生成一个无空位的数独
    state getSudoku(int level);//生成一个难度为level的数独题

private:
    std::stack<state> stateStack;
    //isIn为true：要把number填入blockNumber格子；为false：number禁止填入blockNumber格子
    state changeState(state initialState, int blockNumber, int number, bool isIn);
    //求出某个二进制数的最靠后的为1的位
    int getFirstSolution(int number);

};

#endif // SUDOKUALGORITHM_H
