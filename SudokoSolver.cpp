#include<iostream>
using namespace std;
bool isSafe(int Board[][9],int val,int row,int col){
    for(int i=0;i<9;i++){
        if(Board[row][i]==val){
            return false;
        }
        if(Board[i][col]==val){
            return false;
        }
        if(Board[3*(row/3)+i/3][3*(col/3)+i%3]==val){
            return false;
        }
    }
    return true;
}
bool Solve(int Board[][9]){
    for(int row=0;row<9;row++){
        for(int col=0;col<9;col++){
            if(Board[row][col]==0){
                for(int val=1;val<=9;val++){
                    if(isSafe(Board,val,row,col)){
                        Board[row][col]=val;
                        bool nextSolve=Solve(Board);
                        if(nextSolve){
                            return true;
                        }else{
                            Board[row][col]=0;
                        }
                    }
                }
                return false;
            }
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<Board[i][j]<<" ";
        }
        cout<<"\n";
    }

}
int main(){
    int Board[9][9]={
                {5,3,0,0,7,0,0,0,0},
                {6,0,0,1,9,5,0,0,0},
                {0,9,8,0,0,0,0,6,0},
                {8,0,0,0,6,0,0,0,3},
                {4,0,0,8,0,3,0,0,1},
                {7,0,0,0,2,0,0,0,6},
                {0,6,0,0,0,0,2,8,0},
                {0,0,0,4,1,9,0,0,5},
                {0,0,0,0,8,0,0,7,9},
            };
            Solve(Board);
            return 0;
}