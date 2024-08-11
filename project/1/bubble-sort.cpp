#include <stdio.h>
using namespace std;
#define MAXN 10000000
//冒泡排序，第一次上机作业

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
int n;
int a[MAXN];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    bubblesort(a,n);
    for(int i=0;i<n;i++)printf("%d ",a[i]);
    return 0;
}