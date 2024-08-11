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
int a[MAXN];

void swap(int *m, int *n){
    int tmp;tmp= *m;*m = *n;*n = tmp;
}
int partition(int l,int r){
    int x=a[r];
    int i=l-1;
    for(int j=l;j<r;j++){
        if(a[j]<=x){
            i++;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i+1],&a[r]);
    return i+1;
}
int random_partition(int l, int r){
    int t=l+rand() % (r-l+1);
    swap(&a[t],&a[r]);
    return partition(l,r);
}
int random_select(int l,int r,int num){
    if(l==r)return a[l];
    int pivot=random_partition(l,r);
    int k=pivot-l+1;
    if(num==k)return a[pivot];
    else if(num<k)return random_select(l,pivot-1,num);
    else return random_select(pivot+1,r,num-k);
}
int main(){
    cout<<"This is the test for rand-select algorithm:"<<endl;
    srand(time(NULL));
    clock_t start, stop;
    for(int i=1;i<=10;i++)strcpy(filename[i],tmp1);
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
    int tmp=100;
    cout<<"Task2:random 1e2,1e3,1e4,1e5,1e6, get 0.5N big num:"<<endl;
    for(int i=1;i<=5;i++){
        ifstream fin(filename[i]);
        for(int j=0;j<tmp;j++)fin>>a[j];
        start=clock();
        cout<<"0.5N: "<<random_select(0,tmp-1,tmp/2);
        stop=clock();
        cout<<" Scale: "<<tmp<<" Time: "<<1000*((double) (stop - start) / CLOCKS_PER_SEC)<<"ms"<<endl;
        fin.close();
        tmp*=10;
    }

    cout<<"Task3:random 1e6, get 0.2N,0.4N,0.6N,0.8N big num:"<<endl;
    tmp=1000000;
    ifstream fin1(filename[5]);
    for(int i=0;i<tmp;i++)fin1>>a[i];
    fin1.close();
    for(int i=1;i<=4;i++){
        start=clock();
        cout<<"0."<<(i*2)<<"N:"<<random_select(0,tmp-1,(tmp/5)*i)<<" ";
        stop=clock();
        cout<<"Time: "<<1000*((double) (stop - start) / CLOCKS_PER_SEC)<<"ms"<<endl;
    }
    cout<<"Task4:increase 1e2,1e3,1e4,1e5,1e6, get 0.5N big num:"<<endl;
    tmp=100;
    for(int i=1;i<=5;i++){
        ifstream fin(filename[i+5]);
        for(int j=0;j<tmp;j++)fin>>a[j];
        start=clock();
        cout<<"0.5N: "<<random_select(0,tmp-1,tmp/2);
        stop=clock();
        cout<<" Scale: "<<tmp<<" Time: "<<1000*((double) (stop - start) / CLOCKS_PER_SEC)<<"ms"<<endl;
        fin.close();
        tmp*=10;
    }
    return 0;
}