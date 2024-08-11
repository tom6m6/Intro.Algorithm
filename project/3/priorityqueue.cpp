#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
int a[10000000+6],n;

void heapify(int a[],int i,int n){
    int tmp,tmp1;
    if((2*i<=n) && (a[2*i]>a[i]))tmp=2*i;
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
    ifstream fin("data.txt");
    ofstream fout("result.txt");
    fin>>n;for(int i=1;i<=n;i++)fin>>a[i];
    clock_t start,stop;
    start=clock();
    heapsort(a,n);
    stop=clock();
    for(int i=1;i<=n;i++)fout<<a[i]<<" ";
    cout<<"Time:"<<1000*(((double) (stop - start))/CLOCKS_PER_SEC)<<"ms"<<endl;
    fin.close();
    fout.close();
    return 0;
}