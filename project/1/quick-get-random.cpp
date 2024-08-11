#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string.h>
using namespace std;
//没办法，这个是用来快速得到需要的数据集而生的
bool cmp(int a, int b){return b < a;}
int s,t,a[1000000+66];

char filename[17][128];
char tmp1[]="./dataset/randnum-",tmp2[]=".txt",tmp3[10]="100";
char tmp4[]="-increase",tmp5[]="-decrease",tmp6[]="-rand";

void Solve_Filename(){
    for(int i=1;i<=15;i++){
        strcpy(filename[i],tmp1);
    }
    for(int i=2;i<=6;i++){
        strcat(filename[1+(i-2)*3],tmp3);
        strcat(filename[2+(i-2)*3],tmp3);
        strcat(filename[3+(i-2)*3],tmp3);

        strcat(filename[1+(i-2)*3],tmp4);
        strcat(filename[2+(i-2)*3],tmp5);
        strcat(filename[3+(i-2)*3],tmp6);

        strcat(filename[1+(i-2)*3],tmp2);
        strcat(filename[2+(i-2)*3],tmp2);
        strcat(filename[3+(i-2)*3],tmp2);
        tmp3[i+1]='0';
        tmp3[i+2]='\0';
    }
}

int main() {
    s=0,t=0x7FFFFF00;//防止溢出
    srand(time(0));
    Solve_Filename();
    int tmp=100;
    for(int i=2;i<=6;i++){

        ofstream fout1(filename[1+(i-2)*3]);
        ofstream fout2(filename[2+(i-2)*3]);
        ofstream fout3(filename[3+(i-2)*3]);

        for(int i=0;i<tmp;i++)a[i]=s+rand()%(t-s+1);
        for(int i=0;i<tmp;i++)fout3<<a[i]<<" ";
        sort(a,a+tmp);
        for(int i=0;i<tmp;i++)fout1<<a[i]<<" ";
        sort(a,a+tmp,cmp);
        for(int i=0;i<tmp;i++)fout2<<a[i]<<" ";
        fout1.close();
        fout2.close();
        fout3.close();

        tmp*=10;
    }


    return 0;
}
