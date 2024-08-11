#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstdio>
#include<cstring>
#define MAXN 2050
using namespace std;
int A[MAXN][MAXN],B[MAXN][MAXN],C[MAXN][MAXN];
//A,B作为输入矩阵 C作为结果矩阵
int n;
int main(){
    std::ios::sync_with_stdio(false);
    ifstream fin("data.txt");
    ofstream fout("result.txt");
    fin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)fin>>A[i][j];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)fin>>B[i][j];
    }
    //这里涉及到一个问题，我们以什么顺序进行运算？
    //根据《深入理解计算机系统》(CSAPP第三版，机械工业出版社)Page448-450
    //我们可以知道采用kij或者ikj版本的不命中率最低，时间效率最高
    //我在这个问题中采用kij版本书写代码
    int tmp;
    clock_t start, stop;
    start=clock();
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            tmp=A[i][k];
            for(int j=0;j<n;j++){
                C[i][j]+=tmp*B[k][j];
            }
        }
    }
    stop=clock();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fout<<C[i][j]<<" ";
        }
        fout<<endl;
    }
    cout<<"Time: "<<1000*((double)(stop - start) / CLOCKS_PER_SEC)<<"ms"<< endl;
    fin.close();
    fout.close();
    return 0;
}