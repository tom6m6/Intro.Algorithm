#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <string.h>
#define MAXN 1000006
using namespace std;
struct PACK{int index,value;};
int a[MAXN];
char filename[13][128];
char tmp1[]="./data/randnum-";
char tmp2[]=".txt";
char tmp3[10]="100";
char tmp4[]="-rand",tmp5[]="-increase";
void swap(int *m, int *n);

int partition(int l,int r,int pivot){
    int tmp=a[pivot];
    int i=l-1;
    for(int j=l;j<=r;j++){
        if(a[j]<=tmp){
            i++;swap(&a[i], &a[j]);
        }
    }
    swap(&a[i],&a[pivot]);
    return i;
}
void insert_sort(int a[],int l, int r){
    int key,j;
    for(int i=l;i<=r;i++){
        key=a[i];
        j=i-1;
        while(j>=l && a[j]>key){
            a[j+1]=a[j];j--;
        }
        a[j+1]=key;
    }
}
PACK select(int l,int r,int num){
    if(r-l<=4){
        insert_sort(a,l,r);
        PACK pack1;
        pack1.index=l+num-1;
        pack1.value=a[pack1.index];
        return pack1;
    }
    if(r-l<140){
        insert_sort(a,l,r);
        PACK pack1;
        pack1.index=l+num-1;
        pack1.value=a[l+num-1];
        return pack1;
    }
    for(int i=0;i*5<=(r-l);i++){
        if(l+i*5+4>r){
            insert_sort(a,l+i*5,r);
            int mid=l+i*5+(r-(l+i*5))/2;
            swap(&a[mid],&a[l+i]);
        }else{
            insert_sort(a,l+i*5,l+i*5+4);
            int mid=l+i*5+2;
            swap(&a[mid],&a[l+i]);
        }
    }
    PACK pack2=select(l,l+(r-l)/5,((r-l)/5+1)/2);
    int pivot=partition(l,r,pack2.index);
    int k=pivot-l+1;
    if(num==k) {
        PACK pack3;
        pack3.index=pivot;pack3.value=a[pivot];
        return pack3;
    }else if(num<k)return select(l,pivot-1,num);
    else return select(pivot+1,r,num-k);
}

int main(){
    cout<<"This is the test for SELECT algorithm:"<<endl;
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
        cout<<"0.5N: "<<select(0,tmp-1,tmp/2).value;
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
        cout<<"0."<<(i*2)<<"N:"<<select(0,tmp-1,(tmp/5)*i).value<<" ";
        stop=clock();
        cout<<"Time: "<<1000*((double) (stop-start)/ CLOCKS_PER_SEC)<<"ms"<<endl;
    }


    cout<<"Task4:increase 1e2,1e3,1e4,1e5,1e6, get 0.5N big num:"<<endl;
    tmp=100;
    for(int i=1;i<=5;i++){
        ifstream fin(filename[i+5]);
        for(int j=0;j<tmp;j++)fin>>a[j];
        start=clock();
        cout<<"0.5N: "<<select(0,tmp-1,tmp/2).value;
        stop=clock();
        cout<<" Scale: "<<tmp<<" Time: "<<1000*((double) (stop-start)/ CLOCKS_PER_SEC)<<"ms"<<endl;
        fin.close();
        tmp*=10;
    }


    return 0;
}
void swap(int *m, int *n){
    int tmp;tmp= *m;*m = *n;*n = tmp;
}