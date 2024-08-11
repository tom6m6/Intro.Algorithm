//要和three-sort.cpp一起编译
// g++ .\test-getans.cpp .\three-sort.cpp -o testcases.exe
#include<iostream>
#include<fstream>
#include<cstdio>
#include<stdio.h>
#include<ctime>
#include<string.h>
using namespace std;
int a[1000000+66],b[1000000+66],n;
char filename[17][128];
char tmp1[]="./dataset/randnum-",tmp2[]=".txt",tmp3[10]="100";
char tmp4[]="-increase",tmp5[]="-decrease",tmp6[]="-rand";

extern void bubblesort(int a[],int n);
extern void mergesort(int arr[],int left,int right,int tmp[]);
extern void insertionsort(int arr[],int len);

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

int main(){
    ofstream fout("data.txt");
    clock_t startTime, endTime;
    Solve_Filename();
    int scale=100;
    for(int i=2;i<=6;i++){

        ifstream fin1(filename[1+(i-2)*3]);
        ifstream fin2(filename[2+(i-2)*3]);
        ifstream fin3(filename[3+(i-2)*3]);

        for(n=0;n<scale;n++)fin1>>a[n];
        startTime=clock();
        mergesort(a,0,n-1,b);
        endTime = clock();

        fout<<"Mergesort"<<n<<"Increase"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin1.close();

        for(n=0;n<scale;n++)fin2>>a[n];
        startTime=clock();
        mergesort(a,0,n-1,b);
        endTime = clock();

        fout<<"Mergesort"<<n<<"Decrease"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin2.close();

        for(n=0;n<scale;n++)fin3>>a[n];
        startTime=clock();
        mergesort(a,0,n-1,b);
        endTime = clock();

        fout<<"Mergesort"<<n<<"Rand"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin3.close();

        scale*=10;
    }

    scale=100;
    for(int i=2;i<=6;i++){

        ifstream fin1(filename[1+(i-2)*3]);
        ifstream fin2(filename[2+(i-2)*3]);
        ifstream fin3(filename[3+(i-2)*3]);

        for(n=0;n<scale;n++)fin1>>a[n];

        startTime=clock();
        insertionsort(a,n);
        endTime = clock();

        fout<<"Insertsort"<<n<<"Increase"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin1.close();

        for(n=0;n<scale;n++)fin2>>a[n];
        startTime=clock();
        insertionsort(a,n);
        endTime = clock();

        fout<<"Insertsort"<<n<<"Decrease"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin2.close();


        for(n=0;n<scale;n++)fin3>>a[n];
        startTime=clock();
        insertionsort(a,n);
        endTime = clock();

        fout<<"Insertsort"<<n<<"Rand"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;       
        fin3.close();

        scale*=10;
    }



    scale=100;
    for(int i=2;i<=6;i++){

        ifstream fin1(filename[1+(i-2)*3]);
        ifstream fin2(filename[2+(i-2)*3]);
        ifstream fin3(filename[3+(i-2)*3]);

        for(n=0;n<scale;n++)fin1>>a[n];
        startTime=clock();
        bubblesort(a,n);
        endTime = clock();

        fout<<"Bubblesort"<<scale<<"Increase"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin1.close();

        for(n=0;n<scale;n++)fin2>>a[n];
        startTime=clock();
        bubblesort(a,n);
        endTime = clock();

        fout<<"Bubblesort"<<scale<<"Decrease"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin2.close();

        for(n=0;n<scale;n++)fin3>>a[n];
        startTime=clock();
        bubblesort(a,n);
        endTime = clock();

        fout<<"Bubblesort"<<scale<<"Rand"<<"RunTime: "<<(1000*( (double) (endTime - startTime) / CLOCKS_PER_SEC))<<"ms"<<endl;
        fin3.close();

        scale*=10;
    }
    fout.close();
    return 0;
}