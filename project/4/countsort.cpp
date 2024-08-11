#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define MAXN 1000006
#define MAXM 20000006
using namespace std;
int n,maxx=-66666;
int a[MAXN],b[MAXN],tmp[MAXM];
int main(){
    clock_t startTime, endTime;
    ifstream fin("data.txt");
    ofstream fout("result.txt");
    
    fin>>n;
    for(int i=1;i<=n;i++){
        fin>>a[i];
        if(a[i]>maxx)maxx=a[i];
    }
    startTime=clock();
    //tmp是全局的，自动初始化就是0
    for(int i=1;i<=n;i++)tmp[a[i]]+=1;
    for(int i=1;i<=maxx;i++)tmp[i]+=tmp[i-1];
    for(int i=n;i>=1;i--){
        b[tmp[a[i]]]=a[i];
        --tmp[a[i]];
    }
    endTime=clock();
    for(int i=1;i<=n;i++){
        fout<<b[i]<<" ";
    }
    cout<<"Time: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
    
    fin.close();
    fout.close();
}