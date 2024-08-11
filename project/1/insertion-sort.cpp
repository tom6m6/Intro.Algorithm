#include<cstdio>
using namespace std;
#define MAXN 10000000
//插入排序，第一次上机作业
int n;
int a[MAXN];
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

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    insertionsort(a,n);
    for (int i=0;i<n;i++)printf("%d ",a[i]);
    return 0;
}