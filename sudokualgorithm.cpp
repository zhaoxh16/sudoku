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
            if(stateNow.solutionNumber[i]!=-1)
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
    if(number == 0)
        return initialState;
    if(isIn==false){
        int temp = initialState.number[blockNumber]&~(1<<(number-1));
        if(initialState.number[blockNumber]!=temp){
            --initialState.solutionNumber[blockNumber];
            initialState.number[blockNumber] = initialState.number[blockNumber]&~(1<<(number-1));
        }
    }
    //如果isIn是true，需要把blockNumber格子中放入number，并把相关的格子放number的可能去掉
    else{
        //添加
        initialState.number[blockNumber] = (1<<(number-1));
        initialState.solutionNumber[blockNumber] = -1;
        --initialState.blank;

        int x = blockNumber%9;
        int y = blockNumber/9;

        int tempx = x;
        int tempy = y*9;

        //行列排除
        for(int i=0;i<9;i++){
            if(i!=y){
                int temp = (initialState.number[tempx]&~(1<<(number-1)));
                if(initialState.number[tempx] != temp){
                    initialState.number[tempx] = temp;
                    --initialState.solutionNumber[tempx];
                }
            }
            tempx+=9;
            if(i!=x){
                int temp = (initialState.number[tempy]&~(1<<(number-1)));
                if(initialState.number[tempy] != temp){
                    initialState.number[tempy] = temp;
                    --initialState.solutionNumber[tempy];
                }
            }
            ++tempy;
        }

        //小九宫格排除
        int bigBlockNumber = x/3+y/3*3;
        int firstNumber = bigBlockNumber/3*27+bigBlockNumber%3*3;
        for(int i=0;i<9;i++){
            int changeNumber = i/3*9+i%3+firstNumber;
            if(changeNumber!=blockNumber){
                int temp = (initialState.number[changeNumber]&~(1<<(number-1)));
                if(initialState.number[changeNumber] != temp){
                    initialState.number[changeNumber] = temp;
                    --initialState.solutionNumber[changeNumber];
                }
            }
        }

    }
    return initialState;
}

int SudokuAlgorithm::getFirstSolution(int number){
    for(int i=0;i<9;i++){
        if(((number>>i)&1)==1)
            return i+1;
    }
    return 0;
}

state SudokuAlgorithm::initializeState(int* number){
    state myState;
    myState.blank = 81;
    for(int i=0;i<81;i++){
        myState.number[i]=1023;
        myState.solutionNumber[i]=9;
    }
    //temp
    int testNumbers[81];
    for(int i=0;i<81;i++){
        testNumbers[i]=number[i];
    }
    //temp end
    for(int i=0;i<81;i++){
        if(number[i]!=0)
            myState=changeState(myState,i,number[i],true);
    }
    return myState;
}

int SudokuAlgorithm::getSolutionNumber(state initialState){
    if(initialState.blank==solve(initialState).blank)
        return 0;
    else{
        if(stateStack.empty())
            return 1;
        state nowState = stateStack.top();
        stateStack.pop();
        if(nowState.blank==solve(nowState).blank)
            return 1;
        else
            return 2;
    }
}

void SudokuAlgorithm::reset(){
    while(!stateStack.empty())
        stateStack.pop();
}

state SudokuAlgorithm::getCompleteSudoku(){
    srand(unsigned(time(NULL)));
    reset();
    //1. 设置初始状态
    int number = 1;
    int bigBlockNumber = 0;
    state nowState;
    nowState.blank = 81;
    for(int i=0;i<81;i++){
        nowState.number[i]=1023;
        nowState.solutionNumber[i]=9;
    }

    while(1){
        //2. 搜索允许填number的格子
        int firstNumber = bigBlockNumber/3*27+bigBlockNumber%3*3;//该九宫格第一个格子的编号
        vector<int> allowedBlockNumber;
        for(int i=0;i<9;i++){
            int changeNumber = i/3*9+i%3+firstNumber;
            //该格子是否能填该数字
            if(nowState.solutionNumber[changeNumber]!=-1)
                if(((nowState.number[changeNumber]>>(number-1))&1)==1)
                    allowedBlockNumber.push_back(changeNumber);
        }

        //3. 判断是否有能填该数字的格子
        if(allowedBlockNumber.size()==0){
            nowState = stateStack.top();
            stateStack.pop();
            //回滚
            if(bigBlockNumber != 0)
                --bigBlockNumber;
            else{
                bigBlockNumber = 8;
                --number;
            }
            continue;
        }

        //4. 生成随机数
        int randomNumber = rand()%allowedBlockNumber.size();
        int blockNumber = allowedBlockNumber[randomNumber];

        //5. 将不填该数字的状态push
        stateStack.push(changeState(nowState,blockNumber,number,false));

        //6. 填入该数字
        nowState = changeState(nowState,blockNumber,number,true);

        //7. 判断
        if(number == 9&& bigBlockNumber == 8)
            break;
        else if(bigBlockNumber == 8){
            ++number;
            bigBlockNumber = 0;
        }else
            ++bigBlockNumber;
    }
    return nowState;
}

state SudokuAlgorithm::getSudoku(int level){
    //生成一个完整解
    state initialState = getCompleteSudoku();
    state nowState;
    int numbers[81];
    for(int i=0;i<81;i++){
        for(int j=0;j<9;j++){
            if(initialState.number[i]==1){
                numbers[i]=j+1;
                break;
            }
            else
                initialState.number[i]/=2;
        }
    }
    //生成一个随机数列
    srand(unsigned(time(NULL)));
    vector<int> series;
    for(int i=0;i<81;i++){
        series.push_back(i);
    }
    for(int i=0;i<10000;i++)
        swap(series[rand()%81],series[rand()%81]);

    //开始挖洞
    int total = 0;//一共挖去的洞的数量
    for(int i=0;i<81;i++){
        int blockNumber = series[i];
        int number = numbers[blockNumber];
        numbers[blockNumber] = 0;
        reset();
        nowState = initializeState(numbers);
        if(getSolutionNumber(nowState) == 1){
            ++total;
            if(total == level*6-1)
                break;
            continue;
        }
        else{
            numbers[blockNumber] = number;
        }
    }
    nowState = initializeState(numbers);
    for(int i=0;i<81;i++){
        if(numbers[i]==0)
            nowState.number[i] = 0;
    }
    return nowState;//这个nowState并不是真正的能解的，只是为了获取数组临时构造的
}
