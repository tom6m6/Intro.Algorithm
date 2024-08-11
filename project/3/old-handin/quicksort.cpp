#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
int a[10000000+6],n;
int partition(int a[],int left,int right){
    int tmp=a[right];
    int i=left-1;
    int tmp1;
    for(int j=left;j<right;j++){
        if(a[j]<=tmp){
            ++i;
            tmp1=a[i];a[i]=a[j];a[j]=tmp1;
        }
    }
    tmp1=a[i+1];a[i+1]=a[right];a[right]=tmp1;
    return 1+i;
}
void quicksort(int a[],int left,int right){
    if(left<right){
        int mid=partition(a,left,right);
        quicksort(a,left,mid-1);
        quicksort(a,mid+1,right);
    }
}
int main(){
    ifstream fin("data.txt");
    ofstream fout("result.txt");
    fin>>n;for(int i=0;i<n;i++)fin>>a[i];
    clock_t start,stop;
    start=clock();
    quicksort(a,0,n-1);
    stop=clock();
    for(int i=0;i<n;i++)fout<<a[i]<<" ";
    cout<<"Time:"<<1000*(((double) (stop - start))/CLOCKS_PER_SEC)<<"ms"<<endl;
    fin.close();
    fout.close();
    return 0;
}