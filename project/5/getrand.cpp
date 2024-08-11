#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string.h>
#define MAXN 1000006
using namespace std;
char filename[13][128];
char tmp1[]="./data/randnum-";
char tmp2[]=".txt";
char tmp3[10]="100";
char tmp4[]="-rand",tmp5[]="-increase";

//int n,m,t;
int m=66666666;
//t=0 随机取值 t=1顺序递增 t=2顺序递减
int a[MAXN];
bool cmp(int a,int b){
    return b<a;
}
int main(){
    for(int i=1;i<=10;i++){
        strcpy(filename[i],tmp1);
    }
    for(int i=1;i<=5;i++){
        strcat(filename[i],tmp3);
        strcat(filename[i],tmp4);
        strcat(filename[i],tmp2);
        strcat(filename[i+5],tmp3);
        strcat(filename[i+5],tmp5);
        strcat(filename[i+5],tmp2);
        tmp3[i+2]='0';
        tmp3[i+3]='\0';
    }

    srand(time(NULL));
    int tmp=100;
    for(int i=1;i<=5;i++){
        ofstream fout1(filename[i]);
        ofstream fout2(filename[i+5]);
        //fout1<<tmp<<endl;fout2<<tmp<<endl;
        for(int i=1;i<=tmp;i++)a[i]=(double)rand()/RAND_MAX * (m)+1;
        for(int i=1;i<=tmp;i++)fout1<<a[i]<<" ";
        sort(a,a+tmp);
        for(int i=1;i<=tmp;i++)fout2<<a[i]<<" ";
        fout1.close();fout2.close();
        tmp*=10;
    }
    return 0;
}