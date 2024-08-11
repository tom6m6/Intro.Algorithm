#include <cstdio>
#include <ctime>
using namespace std;
#define MAXN 10000000
//归并排序，第一次上机作业
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
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    mergesort(a,0,n-1,b);
    for(int i=0;i<n;i++)printf("%d ",a[i]);
    return 0;
}