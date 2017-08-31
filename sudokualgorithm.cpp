#include "sudokualgorithm.h"

using namespace std;

SudokuAlgorithm::SudokuAlgorithm()
{

}

state SudokuAlgorithm::solve(state initialState){//目前只能判断是否有解
    state stateNow = initialState;//当前的状态
    while(stateNow.blank!=0){//当前状态仍需继续操作
        //1. 遍历所有格子，读出每个空格子解的数量
        stack<int> solutionNumber[10];//存储有不同solutionNumber的解的格子的编号
        for(int i=0;i<81;i++){
            solutionNumber[stateNow.solutionNumber[i]].push(i);
        }

        //2. 找解数量最少的格子
        //目前不是随机找，以后应该优化一下？
        int blockNumber;//即将被操作的格子的编号
        int flag = 0;//flag记录找到的格子的解的数量，0为无解，1为唯一解，2为多解
        for(int i=0;i<10;i++){
            if(!solutionNumber[i].empty()){
                blockNumber = solutionNumber[i].top();
                flag = i;
                break;
            }
        }

        //3. 判断解的数量
        int number;//将要被填入的数字
        if(flag==0){//存在无解的格子
            if(!stateStack.empty()){//如果stack中还有别的状态
                stateNow = stateStack.top();//将上一个状态pop出来
                stateStack.pop();
            }
            else//如果数独无解
                return initialState;//返回最初的状态（不更改状态）
            continue;//重新开始操作
        }else if(flag == 2){//最少解的格子也有多解
            //求出最小数字解
            number = getFirstSolution(stateNow.number[blockNumber]);
            //将无法填入最小数字解的状态push
            stateStack.push(changeState(stateNow,blockNumber,number,false));
        }else{//存在单解的格子
            number = getFirstSolution(stateNow.number[blockNumber]);
        }

        //4. 填入最小数字解
        stateNow = changeState(stateNow,blockNumber,number,true);

        //继续循环
    }
    return stateNow;
}

state SudokuAlgorithm::changeState(state initialState, int blockNumber, int number, bool isIn){
    //如果isIn是false，需要把blockNumber的格子中放number的可能去掉
    if(isIn==false){
        int temp = initialState.number[blockNumber]&~(1<<(number-1));
        if(initialState.number[blockNumber]!=temp){
            --initialState.solutionNumber[blockNumber];
            initialState.number[blockNumber] = initialState.number[blockNumber]&~(1<<(number-1));
        }
    }
    //如果isIn是true，需要把blockNumber格子中放入number，并把相关的格子放number的可能去掉
    else{
        initialState.number[blockNumber] = (1<<(number-1));
        initialState.solutionNumber[blockNumber] = 0;
        --initialState.blank;

        int x = blockNumber%9;
        int y = blockNumber/9;

        int tempx = x;
        int tempy = y*9;

        for(int i=0;i<9;i++){
            if(i!=y){
                int temp = (initialState.number[tempx]&~(1<<(number-1)));
                if(initialState.number[tempx] != temp){
                    initialState.number[tempx] = temp;
                    --initialState.solutionNumber[tempx];
                }
                tempx+=9;
            }
            if(i!=x){
                int temp = (initialState.number[tempy]&~(1<<(number-1)));
                if(initialState.number[tempy] != temp){
                    initialState.number[tempy] = temp;
                    --initialState.solutionNumber[tempy];
                }
                ++tempy;
            }
        }
    }
    return initialState;
}

int SudokuAlgorithm::getFirstSolution(int number){
    for(int i=0;i<9;i++){
        if((number&(1<<i))!=0)
            return i+1;
    }
    return 0;
}
