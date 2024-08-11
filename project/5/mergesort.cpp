#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <string.h>
using namespace std;
#define MAXN 1000006
//归并排序
char filename[13][128];
char tmp1[]="./data/randnum-";
char tmp2[]=".txt";
char tmp3[10]="100";
char tmp4[]="-rand",tmp5[]="-increase";

int n;
int a[MAXN],b[MAXN];
void merge(int arr[],int left,int mid,int right,int tmp[]){
    int i=left;
    int j=mid+1;
    int t = 0;
    while (i<=mid && j<=right){
        if (arr[i]<=arr[j]){
            tmp[t++]=arr[i++];
        }else{
            tmp[t++]=arr[j++];
        }
    }
    while(i<=mid)tmp[t++]=arr[i++];
    while(j<=right)tmp[t++]=arr[j++];
    t=0;
    while(left<=right)arr[left++]=tmp[t++];
    
}
void mergesort(int arr[],int left,int right,int tmp[]){
    if (left<right){
        int mid=(left+right)/2;
        mergesort(arr,left,mid,tmp);
        mergesort(arr,mid+1,right,tmp);
        merge(arr,left,mid,right,tmp);
    }
    
}

int main(){
    clock_t start, stop;
    cout<<"This is the test for Merge-sort algorithm:"<<endl;
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
    cout<<"Task:random 1e2,1e3,1e4,1e5,1e6, get 0.5N big num:"<<endl;
    int tmp=100;
    for(int i=1;i<=5;i++){
        ifstream fin(filename[i]);
        for(int j=0;j<tmp;j++)fin>>a[j];
        start=clock();
        mergesort(a,0,tmp-1,b);
        cout<<"0.5N: "<<a[tmp/2];
        stop=clock();
        cout<<" Scale: "<<tmp<<" Time: "<<1000*((double) (stop - start) / CLOCKS_PER_SEC)<<"ms"<<endl;
        fin.close();
        tmp*=10;
    }

    return 0;
}