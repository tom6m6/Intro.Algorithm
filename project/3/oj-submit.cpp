#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
using namespace std;
int a[1000000+6],n;

void heapify(int a[],int i,int n){
    int tmp,tmp1;
    if((2*i <= n ) && (a[2*i]>a[i]))tmp=2*i;
    else tmp=i;

    if((2*i+1<= n) &&  (a[2*i+1]>a[tmp]))tmp=2*i+1;

    if(tmp!=i){
        tmp1=a[i];a[i]=a[tmp];a[tmp]=tmp1;
        heapify(a,tmp,n);
    }
}
void buildheap(int a[],int n){
    for(int i=(n/2);i>=1;i--)heapify(a,i,n);
}
void heapsort(int a[],int n){
    buildheap(a,n);
    int tmp,tmplen=n,cnt=1;
    for(int i=n;i>=2;i--){
        int tmp=a[1];a[1]=a[i];a[i]=tmp;
        --tmplen;++cnt;
        heapify(a,1,tmplen);
    }
    return;
}
int main(){

    cin>>n;for(int i=1;i<=n;i++)cin>>a[i];;
    heapsort(a,n);
    for(int i=1;i<=n;i++)cout<<a[i]<<" ";
    return 0;
}