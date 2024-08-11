//写好接口，方便调用
#include <stdio.h>
using namespace std;
void bubblesort(int a[],int n){
    int tmp;
    for (int i=0;i<n-1;i++){
        for (int j=0;j+i+1<n;j++) {
            if (a[j]>a[j+1]){
                tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
    }
    return;
}
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
void insertionsort(int arr[],int len){
    int tmp,i;
    for(int j=1;j<len;j++){
        tmp=arr[j];
        i=j-1;
        while(i>0 && arr[i]>tmp){
            arr[i+1]=arr[i];
            i--;
        }
        arr[i+1]=tmp;
    }
}